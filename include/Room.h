#ifndef ROOM_H
#define ROOM_H

#include "Thing.h"
#include "Timer.h"
#include "Updatable.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Room : public Updatable
{
    friend class PuttyParser;
    public:
        Room();
        virtual ~Room();

        //Static
        string name;
        string description;
        vector<Timer> timers;

        //Dynamic
        map<string, Thing*> contents;

        //Functions
        void look();
        void print();

    private:
        vector<string> contentNames;
};

#endif // ROOM_H
