#include "Room.h"

#define MAX_COLS 80
#define MAX_ROWS 25

using namespace std;

Room::Room()
{
    //ctor
}

Room::~Room()
{
    //dtor
}

void safePrint(string content, int *row)
{
    if (content != "")
    {
        istringstream iss(content);
        int col = 0;
        while (iss)
        {
            string word;
            iss >> word;
            col += word.length();
            if (col > MAX_COLS)
            {
                cout << endl;
                (*row)++;
                col = 0;
            }
            cout << word << " ";
            col++;
        }
    }
    cout << endl;
    (*row)++;
}

void Room::look()
{
    int row = 0;
    safePrint(name, &row);
    safePrint(description, &row);
    for (auto item : contents)
        if (item.second->isFree)
            safePrint("There is " + item.second->ArticleName() + " here.", &row);
//    for (int i = row; i < MAX_ROWS-1; i++)
//        cout << endl;
}

void Room::print()
{
    cout << "|| " << name << " ||" << endl;

    if (!contentNames.empty())
    {
        cout << "Contents:\t";
        for (string content : contentNames)
            cout << content << ", ";
        cout << endl;
    }

    if (description != "")
        cout << endl << "=====" << endl << description << endl << "=====" << endl << endl;

    cout << "----------------------------------------" << endl;
}

void update(){
    for (auto timer: timers)
        timer.update();
    for (auto thing: things)
        thing.second.update();
}
