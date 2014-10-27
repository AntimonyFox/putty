#ifndef PUTTYPARSER_H
#define PUTTYPARSER_H

#include <string>
#include <vector>
#include <map>
#include "Room.h"
#include "Thing.h"

using namespace std;

class PuttyParser
{
    public:
        PuttyParser();
        virtual ~PuttyParser();
        void parse(string path);
    protected:
    private:
        map<string, Room*> rooms;
        map<string, Thing*> things;
};

#endif // PUTTYPARSER_H
