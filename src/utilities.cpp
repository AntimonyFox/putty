#include "utilities.h"

#include <iostream>

string ToLower(string lowerMe)
{
    for (unsigned int i = 0; i < lowerMe.length(); ++i)
    {
        if (lowerMe[i] >= 'A' && lowerMe[i] <= 'Z')
        {
            lowerMe[i] += ' ';
        }
    }

    return lowerMe;
}

string RemoveSpaces(string changeMe)
{
    string returnMe = "";

    std::cout << "RemoveSpaces, size: " << changeMe.length() << std::endl;
    for (unsigned int i = 0; i < changeMe.length(); ++i)
    {
        if ((changeMe[i] >= 'A' && changeMe[i] <= 'Z') || (changeMe[i] >= 'a' && changeMe[i] <= 'z'))
        {
            returnMe += changeMe[i];
        }
    }

    return returnMe;
}

string Capitalize(string capMe)
{
    if (capMe[0] >= 'a' && capMe[0] <= 'z')
    {
        capMe[0] -= ' ';
    }

    for (unsigned int i = 1; i < capMe.length(); ++i)
    {
        if (capMe[i] >= 'A' && capMe[i] <= 'Z')
        {
            capMe[i] += ' ';
        }
    }

    return capMe;
}

bool IsNumber(string check)
{
    for (unsigned int i = 0; i < check.size(); ++i)
    {
        if (check[i] < '0' && check[i] > '9')
            return false;
    }
    return true;
}

void RemoveThe(vector<string> *purgeMe)
{
    vector<string>::iterator itr;
    vector<string> *newString = new vector<string>();

    for (itr = purgeMe->begin(); itr < purgeMe->end(); ++itr)
    {
        if (ToLower(*itr) != "the")
        {
            newString->push_back(*itr);
        }
    }

    *purgeMe = *newString;
}

void RemoveFirst(vector<string> *purgeMe)
{
    purgeMe->erase(purgeMe->begin());
}

vector<string> *StringToArguments(string parseMe)
{
    vector<string> *arguments = new vector<string>();
    string curWord = "";
    for (unsigned int i = 0; i < parseMe.length(); ++i)
    {
        char curChar = parseMe[i];
        if (curChar != ' ')
            curWord += curChar;
        else if (curWord != "")
        {
            arguments->push_back(curWord);
            curWord = "";
        }

        if ((i == parseMe.length() - 1) && (curWord != ""))
        {
            arguments->push_back(curWord);
            curWord = "";
        }
    }
    return arguments;
}

string Implode(vector<string> *arguments, string join)
{
    string output = "";
    if (!arguments->empty())
    {
        output += (*arguments)[0];
        for (unsigned int i = 1; i < arguments->size(); i++)
        {
            output += join + (*arguments)[i];
        }
    }
    return output;
}