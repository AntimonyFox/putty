#ifndef PUTTYPARSER_H
#define PUTTYPARSER_H

#include "Room.h"
#include "Thing.h"

#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

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

        string bookTitle(string original);
        string getWord(istringstream* iss);
        bool isDelim(char c);
};

#endif // PUTTYPARSER_H
