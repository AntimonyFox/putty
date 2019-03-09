#include "room.h"

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

string safePrint(string content, int *row)
{
    string output = "";
    if (content != "")
    {
        istringstream iss(content);
        int col = 0;
        while (iss)
        {
            string word;
            iss >> word;
            col += word.length() + 1;
            if (col > MAX_COLS)
            {
                output += "\n";
                (*row)++;
                col = 0;
            }
            output += word + " ";
        }
    }
    output += "\n";
    (*row)++;
    return output;
}

string Room::look()
{
    string output = "";
    int row = 0;
    output += safePrint(name, &row);
    output += safePrint(description, &row);
    for (auto item : contents)
        if (item.second->isFree)
            output += safePrint("There is " + item.second->ArticleName() + " here.", &row);

    for (auto play : players)
        output += safePrint((play.second->name + " is here."), &row);
//    for (int i = row; i < MAX_ROWS-1; i++)
//        cout << endl;
    return output;
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

void Room::update(){
    for (auto timer: timers)
        timer.update();
    for (auto thing : contents)
        thing.second->update();
}
