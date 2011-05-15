#include "AntManager.hpp"

#include <iostream>
#include <cstdlib>

AntSensor Cell::toAntSensor(int tId) {
    AntSensor tmp;

    tmp.smell = smell;
    tmp.smellIntensity = smellIntensity;
    if (isAnt) {
        map<int, MyAnt*>::iterator it = ants.begin();
        while (it != ants.end()) {
            tmp.isFriend &= tId == it->second->getTeamId() ? true : false;
            it++;
        }
        tmp.isEnemy = !tmp.isFriend;
    }
    if (isHill) {
        tmp.isMyHill = tId == teamId ? true : false;
        tmp.isEnemyHill = !tmp.isMyHill;
    }
    tmp.isFood = isFood;
    tmp.isWall = isWall;

    return tmp;
}

AntManager::AntManager(int height, int width, int teamCount, int maxAntCountPerTeam) : height(height), width(width), teamCount(teamCount), maxAntCountPerTeam(maxAntCountPerTeam) {
    int i, j;
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

//    static int cnt = 0;
//    cnt++;

    for (i = 0; i < teamCount; i++) {
        for (j = 0; j < maxAntCountPerTeam; j++) {
            if (!ants[i][j]->isDrawn()) {
                field[ants[i][j]->getPoint()].ants[ants[i][j]->getId()] = ants[i][j];
                field[ants[i][j]->getPoint()].isAnt = true;
                ants[i][j]->Drawn();
                break;
            } else {
                s = getSensors(ants[i][j]->getPoint(), ants[i][j]->getTeamId());
                action = brains[i]->GetAction(*ants[i][j], s.sensors);

                //action processing
                processAction(action, ants[i][j]);
                //cout << cnt << " processed\n";
            }
        }
    }

    redraw();
}

void AntManager::processAction(AntAction& action, MyAnt *ant) {
    Point p = ant->getPoint();

    if (action.putSmell) {
        field[p].smell = action.smell;
        field[p].smellIntensity = 101;
    }

    if (action.actionType == antlogic::GET && !ant->hasFood()) {
        ant->setFood(field[p].food);
        field[p].isFood = false;
        field[p].food = 0;
    } else if (action.actionType == antlogic::PUT && ant->hasFood()) {
        field[p].isFood = true;
        field[p].food = ant->getFood();
        ant->setFood(0);
    } else if (action.actionType == antlogic::MOVE_UP) {
        cout << "id: " << ant->getId() << "; teamId: " << ant->getTeamId() << "; up\n";
        Point p1 = p;
        p1.y++;
        processMovement(p, p1, ant);
    } else if (action.actionType == antlogic::MOVE_DOWN) {
        cout << "id: " << ant->getId() << "; teamId: " << ant->getTeamId() << "; down\n";
        Point p1 = p;
        p1.y--;
        processMovement(p, p1, ant);
    } else if (action.actionType == antlogic::MOVE_RIGHT) {
        cout << "id: " << ant->getId() << "; teamId: " << ant->getTeamId() << "; right\n";
        Point p1 = p;
        p1.x++;
        processMovement(p, p1, ant);
    } else if (action.actionType == antlogic::MOVE_LEFT) {
        cout << "id: " << ant->getId() << "; teamId: " << ant->getTeamId() << "; left\n";
        Point p1 = p;
        p1.x--;
        processMovement(p, p1, ant);
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
    while (it != field.end()) {
        if (it->second.smellIntensity)
            it->second.smellIntensity--;
        if (it->second.isAnt) {
            map<int, MyAnt*>::iterator it1 = it->second.ants.begin();
            while (it1 != it->second.ants.end()) {
                gui->SetAnt(it1->second);
                it1++;
            }
        } else if (it->second.isFood) {
            gui->SetFood(it->second.food);
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
    antgui::ConcreteFood *f;
    Point p;

    while (cur != end) {
        f = new antgui::ConcreteFood(*cur);
        p = f->getPoint();

        field[p].food = f;
        field[p].isFood = true;

        cur++;
    }
}
