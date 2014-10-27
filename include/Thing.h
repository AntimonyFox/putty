#ifndef THING_H
#define THING_H

#include <string>
#include <vector>
using namespace std;

class Thing
{
    public:
        Thing();
        virtual ~Thing();
        void look();

        string appearance;
        string name;
        string filename;

        vector<string> keywords;
        string description;
        vector<string> contents;
        int size = -1;
        int capacity = 0;

        bool isLocked = false;
        bool isFree = false;
        bool isReadable = false;
        bool isAnchored = false;
        bool isContainer = false;
    protected:
    private:
};

#endif // THING_H
