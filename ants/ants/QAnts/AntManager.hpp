#ifndef _ANT_MANAGER_

#define _ANT_MANAGER_

#include "IAntGUI.hpp"
#include "IAntLogic.hpp"

#include <vector>
#include <map>
#include <list>
#include <cstring>

using antgui::Point;
using antgui::Food;
using antlogic::AntSensor;
using antlogic::AntAction;
using antlogic::AntActionType;

using namespace std;

class MyAnt : public antlogic::Ant, public antgui::Ant {
    char *memory;
    int teamId;
    Point p;
    bool drawn; //internal use only
    const int id;
    //food
    bool hFood; //have to set it
    Food *food;
    //freeze
    int count;
    bool frozen; //have to set it
public:
    MyAnt(Point& p, int teamId, int id) : memory(NULL), hFood(false), teamId(teamId), frozen(false), p(p), drawn(false), id(id) {
        memory = new char[antlogic::MAX_MEMORY];
        memset(memory, 0, antlogic::MAX_MEMORY);
    }
    ~MyAnt() {
        delete memory;
    }

    bool isDrawn() const {
        return drawn;
    }
    void Drawn() {
        drawn = true;
    }

    int getId() const {
        return id;
    }

    //food related
    void setFood(Food *f) {
        food = f;
        hFood = static_cast<bool>(f);
    }
    Food *getFood() const {
        return food;
    }

    //freezing functions
    void freeze() {
        frozen = true;
        count = 8;
    }
    int getCount() const {
        return count;
    }
    void decCount() {
        if (count > 0) {
            count--;
            if (count == 0)
                frozen = false;
        }
    }
    //
    void setPoint(Point p1) {
        p = p1;
    }

    //instance
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
};

struct Cell {
    int smell;
    int smellIntensity;
    int teamId;

    bool isAnt;
    bool isHill;
    bool isFood;
    bool isWall;

    map<int, MyAnt*> ants;
    list<Food*> food;

    //methods
    AntSensor toAntSensor(int tId);

    Cell() : smell(0), smellIntensity(0), teamId(-1), isAnt(false), isHill(false), isFood(false), isWall(false) {
    }
    ~Cell() {
        list<Food*>::iterator it = food.begin();
        while (it != food.end()) {
            delete *it;
        }
    }
};

class AntManager {
    int height, width;
    int teamCount;
    int maxAntCountPerTeam;

    int score[4];

    //ants
    vector<antlogic::IAntLogic*> brains;
    vector<vector<MyAnt*> > ants;

    //field
    map<Point, Cell> field;
    Point hillPos[4];

    antgui::IAntGui *gui;

    struct sens {
        AntSensor sensors[3][3];
    };

    void processAction(AntAction& action, MyAnt *ant);
    void processMovement(Point p, Point p1, MyAnt *ant);
    void processBiting(Point p1, MyAnt *ant);
    sens getSensors(Point p, int tId);
    void redraw();
public:
    void step(int num);
    void setGui(antgui::IAntGui *gui_);
    void setFoodGeneretor(antgui::food_iterator *it);

    AntManager(int height, int width, int teamCount, int maxAntCountPerTeam=20);
};

#endif
