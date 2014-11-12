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
        void look();
        void print();
        string name;
        string description;
        map<string, Thing*> contents;

    private:
        vector<string> contentNames;
};

#endif // ROOM_H
