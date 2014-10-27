#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
using namespace std;

class Room
{
    public:
        Room();
        virtual ~Room();
        void look();
        string name;
        string description;
        vector<string> contents;
    protected:
    private:
};

#endif // ROOM_H
