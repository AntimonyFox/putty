#include "Thing.h"
#include <iostream>

Thing::Thing()
{
    //ctor
}

Thing::~Thing()
{
    //dtor
}

string Thing::GetName()
{
    if (name != "")
        return name;
    else
        return filename;
}

string Thing::ArticleName()
{
    string n = GetName();
    string article = (n[0] == 'a' || n[0] == 'e' || n[0] == 'i' || n[0] == 'o' || n[0] == 'u') ? "an" : "a";
    return article + " " + n;
}

void Thing::Look()
{
    cout << " "; for (unsigned int i = 0; i < filename.length()+2; i++) cout << "-"; cout << endl;
    cout << "| " << filename << " |" << endl;
    if (name != "")
        cout << name << endl;
    cout << " "; for (unsigned int i = 0; i < filename.length()+2; i++) cout << "-"; cout << endl;

    if (!keywords.empty())
    {
        cout << "Keywords:\t";
        for (string keyword : keywords)
            cout << keyword << " ";
        cout << endl;
    }

    if (!contents.empty())
    {
        cout << "Contents:\t";
        for (string content : contentNames)
            cout << content << ", ";
        cout << endl;
    }

    if (description != "")
        cout << endl << "=====" << endl << description << endl << "=====" << endl << endl;

    if (size != -1)
        cout << "Size: " << size << endl;

    cout << "Properties: " << endl;
    if (isContainer)
        cout << "\tisContainer (capacity: " << capacity << ") " << endl;
    if (isLocked) cout << "\tisLocked " << endl;
    if (isFree) cout << "\tisFree " << endl;
    if (isReadable) cout << "\tisReadable " << endl;
    if (isAnchored) cout << "\tisAnchored " << endl;
    cout << endl;

    cout << "----------------------------------------" << endl;
}

bool Thing::Turn(string on)
{
    return false;
}

bool Thing::Move()
{
    return false;
}
