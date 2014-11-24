#ifndef THING_H
#define THING_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class Thing
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

        //Dynamic
        map<string, Thing*> contents;
        bool isOpen = false;
        bool isLocked = false;
        bool isFree = false;
        bool isReadable = false;
        bool isAnchored = false;
        bool isContainer = false;
        bool isDrinkable = false;
        int isSwitch = -1;
        bool isMoveable = false;
        bool isEdible = false;
        bool isBreakable = false;
        bool canTie = false;

        //Functions
        void Look();
        bool Turn(string on = "");
        bool Move();
        string Examine();
        string GetName();
        string ArticleName();

    private:
        vector<string> contentNames;
};

#endif // THING_H
