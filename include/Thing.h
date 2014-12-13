#ifndef THING_H
#define THING_H

#include <map>
#include <string>
#include <vector>
#include "Timer.h"
#include "Updatable.h"
#include <sstream>

using namespace std;

class Thing : public Updatable
{
    friend class PuttyParser;
    public:
        Thing();
        virtual ~Thing();

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
        Thing *hides;
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

        //Functions
        string Look();
        string GetName();
        string ArticleName();

    private:
        vector<string> contentNames;
        string hidesName;
};

#endif // THING_H
