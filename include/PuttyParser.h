#ifndef PUTTYPARSER_H
#define PUTTYPARSER_H

#include "Game.h"

#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

using namespace std;

class PuttyParser
{
    public:
        static PuttyParser getInstance();
        void Parse(string path, Game *game);

    private:
        void ParseSwitch(string path, Game *game);
        void ParseChildren(string path, Game *game, DIR *root);
        void ParseSettings(string path, Game *game);
        void ParseRoom(string path, Game *game);
        void ParseThing(string path, Game *game);
        void InflateThings(Game *game);
        void InflateRooms(Game *game);
        string BookTitle(string original);
        string GetWord(istringstream* iss);
        bool IsDelim(char c);
};

#endif // PUTTYPARSER_H
