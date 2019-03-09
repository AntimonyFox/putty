#include "thing.h"
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

string Thing::Look()
{
    string output = "";
    output += " "; for (unsigned int i = 0; i < filename.length()+2; i++) output += "-"; output += "\n";
    output += "| " + filename + " |" + "\n";
    if (name != "")
        output += name + "\n";
    output += " "; for (unsigned int i = 0; i < filename.length()+2; i++) output += "-"; output += "\n";

    if (!keywords.empty())
    {
        output += "Keywords:\t";
        for (string keyword : keywords)
            output += keyword + " ";
        output += "\n";
    }

    if (!contents.empty())
    {
        output += "Contents:\t";
        for (string content : contentNames)
            output += content + ", ";
        output += "\n";
    }

    if (description != "")
        output += "\n=====\n" + description + "\n=====\n\n";

    if (size != -1)
    {
        stringstream iss;
        iss << size;
        output += "Size: " + iss.str() + "\n";
    }

    output += "Properties:\n";
    if (isContainer)
    {
        stringstream iss;
        iss << capacity;
        output += "\tisContainer (capacity: " + iss.str() + ")\n";
    }
    if (isLocked) output += "\tisLocked\n";
    if (isFree) output += "\tisFree\n";
    if (isReadable) output += "\tisReadable\n";
    if (isAnchored) output += "\tisAnchored\n";
    output += "\n";

    output += "----------------------------------------\n";
    return output;
}

void Thing::update(){
    for (auto timer : timers)
        timer.update();

    if (isContainer)
        for (auto thing : contents)
            thing.second->update();
}
