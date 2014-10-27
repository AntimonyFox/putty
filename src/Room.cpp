#include "Room.h"
#include <iostream>

using namespace std;

Room::Room()
{
    //ctor
}

Room::~Room()
{
    //dtor
}

void Room::look()
{
    cout << "|| " << name << " ||" << endl;

    if (!contents.empty())
    {
        cout << "Contents:\t";
        for (string content : contents)
            cout << content << ", ";
        cout << endl;
    }

    if (description != "")
        cout << endl << "=====" << endl << description << endl << "=====" << endl << endl;

    cout << "----------------------------------------" << endl;
}
