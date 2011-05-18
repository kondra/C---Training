#include "AntManager.hpp"

#include <iostream>
#include <cstdlib>

AntSensor Cell::toAntSensor(int tId) {
    AntSensor tmp;

    tmp.smell = smell;
    tmp.smellIntensity = smellIntensity;
    if (isAnt) {
        map<int, MyAnt*>::iterator it = ants.begin();
        tmp.isFriend = true;
        while (it != ants.end()) {
            tmp.isFriend &= (tId == it->second->getTeamId() ? true : false);
            it++;
        }
        tmp.isEnemy = !tmp.isFriend;
    } else {
        tmp.isFriend = tmp.isEnemy = false;
    }
    if (isHill) {
        tmp.isMyHill = tId == teamId ? true : false;
        tmp.isEnemyHill = !tmp.isMyHill;
    } else {
        tmp.isMyHill = tmp.isEnemyHill = false;
    }
    tmp.isFood = isFood;
    tmp.isWall = isWall;

    return tmp;
}

AntManager::AntManager(int height, int width, int teamCount, int maxAntCountPerTeam) : height(height), width(width), teamCount(teamCount), maxAntCountPerTeam(maxAntCountPerTeam) {
    int i, j;
    for (i = 0; i < 4; i++)
        score[i] = 0;
    //resize field
    for (i = 0; i < height + 2; i++) {
        for (j = 0; j < width + 2; j++) {
            field.insert(make_pair(Point(i, j), Cell()));
        }
    }
    //set field points
    //set Walls
    Point p1(-1, -1), p2(-1, width);
    for (i = -1; i < height + 1; i++) {
        p1.x = p2.x = i;
        field[p1].isWall = true;
        field[p2].isWall = true;
    }
    p1.x = -1;
    p2.x = height;
    for (i = -1; i < width + 1; i++) {
        p1.y = p2.y = i;
        field[p1].isWall = true;
        field[p2].isWall = true;
    }
    //set Hills
    i = 0;
    while (i != teamCount) {
        if (i == 0) {
            p1.x = p1.y = 0;
        } else if (i == 1) {
            p1.x = 0;
            p1.y = width - 1;
        } else if (i == 2) {
            p1.x = height - 1;
            p1.y = 0;
        } else if (i == 3) {
            p1.x = height - 1;
            p1.y = width - 1;
        }
        hillPos[i] = p1;
        field[p1].isHill = true;
        field[p1].teamId = i;
        i++;
    }
    //create ants
    ants.resize(teamCount);
    int id = 1;
    for (i = 0; i < teamCount; i++) {
        brains.push_back(antlogic::IAntLogic::GetAntLogic(i));
        for (j = 0; j < maxAntCountPerTeam; j++) {
            ants[i].push_back(new MyAnt(hillPos[i], i, id++));
        }
    }
}

void AntManager::step(int num) {
    sens s;
    AntAction action;

    int i, j;
    for (i = 0; i < teamCount; i++) {
        for (j = 0; j < maxAntCountPerTeam; j++) {
            if (!ants[i][j]->isDrawn()) {
                field[ants[i][j]->getPoint()].ants[ants[i][j]->getId()] = ants[i][j];
                field[ants[i][j]->getPoint()].isAnt = true;
                ants[i][j]->Drawn();
                break;
            } else {
                if (!ants[i][j]->isFrozen()) {
                    s = getSensors(ants[i][j]->getPoint(), ants[i][j]->getTeamId());
                    action = brains[i]->GetAction(*ants[i][j], s.sensors);
                    processAction(action, ants[i][j]);
                }
            }
        }
    }
    redraw();
    for (i = 0; i < teamCount; i++) {
        gui->SetTeamScore(i, score[i]);
        cout << "team: " << i << "; score: " << score[i] << "\n";
    }
}

void AntManager::processAction(AntAction& action, MyAnt *ant) {
    Point p = ant->getPoint();
    Point p1 = p;

    if (action.putSmell) {
        field[p].smell = action.smell;
        field[p].smellIntensity = 101;
    }

    if (action.actionType == antlogic::GET && !ant->hasFood()) {
        if (field[p].isFood) {
            ant->setFood(true);
            field[p].foodCnt--;
            if (field[p].foodCnt == 0)
                field[p].isFood = false;
            if (field[p].isHill)
                score[field[p].teamId]--;
        }
    } else if (action.actionType == antlogic::PUT && ant->hasFood()) {
        if (field[p].isHill)
            score[field[p].teamId]++;
        field[p].isFood = true;
        field[p].foodCnt++;
        ant->setFood(false);
    } else if (action.actionType == antlogic::MOVE_UP) {
        p1.y++;
        processMovement(p, p1, ant);
    } else if (action.actionType == antlogic::MOVE_DOWN) {
        p1.y--;
        processMovement(p, p1, ant);
    } else if (action.actionType == antlogic::MOVE_RIGHT) {
        p1.x++;
        processMovement(p, p1, ant);
    } else if (action.actionType == antlogic::MOVE_LEFT) {
        p1.x--;
        processMovement(p, p1, ant);
    } else if (action.actionType == antlogic::BITE_UP) {
        p1.y++;
        processBiting(p1, ant);
    } else if (action.actionType == antlogic::BITE_DOWN) {
        p1.y--;
        processBiting(p1, ant);
    } else if (action.actionType == antlogic::BITE_RIGHT) {
        p1.x++;
        processBiting(p1, ant);
    } else if (action.actionType == antlogic::BITE_LEFT) {
        p1.x--;
        processBiting(p1, ant);
    } 
}

void AntManager::processBiting(Point p1, MyAnt *ant) {
    if (field[p1].isWall)
        return;
    if (p1.x < 0 || p1.y < 0) {
        cerr << "FUUU\n";
        exit(0);
    }
    map<int, MyAnt*>::iterator it = field[p1].ants.begin(), pos = field[p1].ants.end();
    int min = 10, cnt;
    int tId = ant->getTeamId();
    while (it != field[p1].ants.end()) {
        if (it->second->getTeamId() != tId) {
            cnt = it->second->getCount();
            if (cnt < min) {
                min = cnt;
                pos = it;
            }
        }
        it++;
    }
    if (pos != field[p1].ants.end()) {
        pos->second->freeze();
        if (pos->second->hasFood()) {
            field[p1].foodCnt++;
            field[p1].isFood = true;
            pos->second->setFood(false);
        }
    }
}

void AntManager::processMovement(Point p, Point p1, MyAnt *ant) {
    if (field[p1].isWall)
        return;
    field[p].ants.erase(ant->getId());
    if (field[p].ants.size() == 0)
        field[p].isAnt = false;

    field[p1].ants[ant->getId()] = ant;
    field[p1].isAnt = true;
    ant->setPoint(p1);
}

AntManager::sens AntManager::getSensors(Point p, int tId) {
    sens s;
    Point p1(p);

    p1.x = p.x - 1;
    p1.y = p.y + 1;
    s.sensors[0][0] = field[p1].toAntSensor(tId);
    p1.y = p.y;
    s.sensors[1][0] = field[p1].toAntSensor(tId);
    p1.y = p.y - 1;
    s.sensors[2][0] = field[p1].toAntSensor(tId);

    p1.x = p.x;
    p1.y = p.y + 1;
    s.sensors[0][1] = field[p1].toAntSensor(tId);
    p1.y = p.y;
    s.sensors[1][1] = field[p1].toAntSensor(tId);
    p1.y = p.y - 1;
    s.sensors[2][1] = field[p1].toAntSensor(tId);

    p1.x = p.x + 1;
    p1.y = p.y + 1;
    s.sensors[0][2] = field[p1].toAntSensor(tId);
    p1.y = p.y;
    s.sensors[1][2] = field[p1].toAntSensor(tId);
    p1.y = p.y - 1;
    s.sensors[2][2] = field[p1].toAntSensor(tId);

    return s;
}

void AntManager::redraw() {
    map<Point, Cell>::iterator it = field.begin();
    gui->Clear();
    gui->BeginPaint();
    food.clear();
    while (it != field.end()) {
        if (it->second.smellIntensity) {
            it->second.smellIntensity--;
            if (it->second.smellIntensity == 0)
                it->second.smell = 0;
        }
        if (it->second.isAnt) {
            map<int, MyAnt*>::iterator it1 = it->second.ants.begin();
            while (it1 != it->second.ants.end()) {
                it1->second->decCount();
                gui->SetAnt(it1->second);
                it1++;
            }
        } else if (it->second.isFood) {
            food.push_front(MyFood(it->first, it->second.foodCnt));
            gui->SetFood(&(*food.begin()));
        }
        it++;
    }
    gui->EndPaint();
}

void AntManager::setGui(antgui::IAntGui *gui_) {
    gui = gui_;
}

void AntManager::setFoodGeneretor(antgui::food_iterator *it) {
    antgui::food_iterator end, cur = *it;
    Point p;

    while (cur != end) {
        p = (*cur).getPoint();

        field[p].foodCnt = (*cur).getCount();
        field[p].isFood = true;

        cur++;
    }
}
