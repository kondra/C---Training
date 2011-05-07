#ifndef _ANT_MANAGER_

#define _ANT_MANAGER_

#include "IAntGUI.hpp"
#include "IAntLogic.hpp"

#include <vector>
#include <map>
#include <cstring>

using antgui::Point;
using namespace std;

class LAnt : public antlogic::Ant {
    char *memory;
    bool hFood;
    int teamId;
public:
    LAnt(int teamId) : hFood(false), teamId(teamId) {
        int i;
        memory = new char[antlogic::MAX_MEMORY];
        for (i = 0; i < antlogic::MAX_MEMORY; i++) {
            memory[i] = 0;
        }
    }
    ~LAnt() {
        delete memory;
    }

    void setFood(bool food) {
        hFood = food;
    }

    char *getMemory() const {
        return memory;
    }
    bool hasFood() const {
        return hFood;
    }
    int getTeamId() const {
        return teamId;
    }
};

class GAnt : public antgui::Ant {
    bool hFood;
    bool frozen;
    Point p;
    int teamId;
public:
    GAnt(Point& p, int teamId) : hFood(false), frozen(false), p(p), teamId(teamId) {}

    void freeze() {
        frozen = true;
    }

		bool hasFood() const {
        return hFood;
    }
		bool isFrozen() const {
        return frozen;
    }
		Point getPoint() const {
        return p;
    }
		int getTeamId() const {
        return teamId;
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
    vector<vector<antlogic::Ant*> > l_ants;

    //field
    map<Point, Cell> field;
    vector<vector<antgui::Ant*> > g_ants;
    Point hillPos[4];

    antgui::IAntGui *gui;
public:
    void step(int num);
    void setGui(antgui::IAntGui *gui);
    void setFoodGeneretor(antgui::food_iterator *it);

    AntManager(int height, int width, int teamCount, int maxAntCountPerTeam=50);
};

#endif
