#include "AntManager.hpp"

AntSensor Cell::toAntSensor(int tId) {
    AntSensor tmp;

    bool fr, en;
    fr = teamId == tId ? true : false;
    en = !fr;

    tmp.smell = smell;
    tmp.smellIntensity = smellIntensity;
    if (isAnt) {
        tmp.isFriend = fr;
        tmp.isEnemy = en;
    }
    if (isHill) {
        tmp.isMyHill = fr;
        tmp.isEnemyHill = en;
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
    }
    //create ants
    ants.resize(teamCount);
    for (i = 0; i < teamCount; i++) {
        brains.push_back(antlogic::IAntLogic::GetAntLogic(i));
        for (j = 0; j < maxAntCountPerTeam; j++) {
            ants[i].push_back(new MyAnt(hillPos[i], i));
        }
    }
}

void AntManager::step(int num) {
}

void AntManager::setGui(antgui::IAntGui *gui) {
}

void AntManager::setFoodGeneretor(antgui::food_iterator *it) {
}
