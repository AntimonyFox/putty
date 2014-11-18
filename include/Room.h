#ifndef ROOM_H
#define ROOM_H

#include "Thing.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Room
{
    friend class PuttyParser;
    public:
        Room();
        virtual ~Room();

        //Static
        string name;
        string description;

        //Dynamic
        map<string, Thing*> contents;

        //Functions
        void look();
        void print();

    private:
        vector<string> contentNames;
};

#endif // ROOM_H
