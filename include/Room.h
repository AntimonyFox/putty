#ifndef ROOM_H
#define ROOM_H

#include "Thing.h"
#include "Timer.h"
#include "Updatable.h"

#include <iostream>
#include <map>
#include <memory>
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
        shared_ptr<Room> north;
        shared_ptr<Room> south;
        shared_ptr<Room> east;
        shared_ptr<Room> west;
        shared_ptr<Room> up;
        shared_ptr<Room> down;

        //Dynamic
        map<string, Thing*> contents;

        //Functions
        string look();
        void print();

    private:
        vector<string> contentNames;
        string northName;
        string southName;
        string westName;
        string eastName;
        string upName;
        string downName;
};

#endif // ROOM_H
