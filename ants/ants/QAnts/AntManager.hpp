#ifndef _ANT_MANAGER_

#define _ANT_MANAGER_

#include "IAntGUI.hpp"
#include "IAntLogic.hpp"

#include <vector>
#include <map>
#include <cstring>

using antgui::Point;
using antlogic::AntSensor;

using namespace std;

class MyAnt : public antlogic::Ant, public antgui::Ant {
    char *memory;
    bool hFood;
    int teamId;
    bool frozen;
    Point p;
public:
    MyAnt(Point& p, int teamId) : memory(NULL), hFood(false), teamId(teamId), frozen(false), p(p) {
        memory = new char[antlogic::MAX_MEMORY];
        memset(memory, 0, antlogic::MAX_MEMORY);
    }
    ~MyAnt() {
        delete memory;
    }

    void setFood(bool food) {
        hFood = food;
    }

    //from Logic
    virtual char *getMemory() const {
        return memory;
    }
    virtual bool hasFood() const {
        return hFood;
    }
    virtual int getTeamId() const {
        return teamId;
    }

    //from Gui
    virtual bool isFrozen() const {
        return frozen;
    }
    virtual Point getPoint() const {
        return p;
    }

    //gui specific
    void freeze() {
        frozen = true;
    }

};

struct Cell {
    int smell;
    int smellIntensity;
    int teamId;

    bool isAnt;
    bool isHill;
    bool isFood;
    bool isWall;

    AntSensor toAntSensor(int tId);

    Cell() : smell(0), smellIntensity(0), teamId(-1) {
        isAnt = isHill = isFood = isWall = false;
    }
};

class AntManager {
    int height, width;
    int teamCount;
    int maxAntCountPerTeam;

    //ants
    vector<antlogic::IAntLogic*> brains;
    vector<vector<MyAnt*> > ants;

    //field
    map<Point, Cell> field;
    Point hillPos[4];

    antgui::IAntGui *gui;
public:
    void step(int num);
    void setGui(antgui::IAntGui *gui);
    void setFoodGeneretor(antgui::food_iterator *it);

    AntManager(int height, int width, int teamCount, int maxAntCountPerTeam=50);
};

#endif
