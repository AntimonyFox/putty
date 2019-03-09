#ifndef THING_H
#define THING_H

class Room;

#include <map>
#include <string>
#include <vector>
#include "timer.h"
#include "updatable.h"
#include <sstream>
#include <memory>

using namespace std;

class Thing : public Updatable
{
    friend class PuttyParser;
    public:
        Thing();
        virtual ~Thing();
        virtual void Update();

        //Static
        string appearance;
        string name;
        string filename;
        vector<string> keywords;
        string description;
        int size = -1;
        int capacity = 0;
        vector<Timer> timers;

        //Dynamic
        map<string, Thing*> contents;
        bool isOn = false;
        bool isOpen = false;
        bool isMoved = false;
        bool isLocked = false;
        bool isFree = false;
        bool isEdible = false;
        bool isDrinkable = false;
        bool isReadable = false;
        bool isMovable = false;
        bool isAnchored = false;
        bool isContainer = false;
        bool isBreakable = false;
        bool isToggleable = false;
        Thing *hides;
        shared_ptr<Room> enter;

        //Functions
        string Look();
        string GetName();
        string ArticleName();

    private:
        vector<string> contentNames;
        string hidesName;
        string enterName;
};

#endif // THING_H
