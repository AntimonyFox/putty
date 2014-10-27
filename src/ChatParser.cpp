#include "ChatParser.h"

string ToLower(string lowerMe)
{
    for(int i = 0 ; i < lowerMe.length() ; ++i)
    {
        if(lowerMe[i] >= 65 && lowerMe[i] <= 90)
        {
            lowerMe[i] += 32;
        }
    }

    return lowerMe;
}

void removeThe(vector<string> * purgeMe)
{
    vector<string>::iterator itr;
    vector<string> * newString = new vector<string>();

	for ( itr = purgeMe->begin(); itr < purgeMe->end(); ++itr )
	{
		if(ToLower(*itr) != "the")
        {
            newString->push_back(*itr);
        }
	}

    *purgeMe = *newString;
}

vector<string> ChatParser::Parse(string parseMe)
{
    string curWord = "";
    vector<string> * arguments = new vector<string>();

    for(unsigned int i = 0 ; i < parseMe.length() ; ++i)
    {
        char curString = parseMe[i];
        if(curString != ' ')
            curWord += curString;
        else if(curWord != "")
        {
            arguments->push_back(curWord);
            curWord = "";
        }

        if((i == parseMe.length()-1) && (curWord != ""))
        {
            arguments->push_back(curWord);
            curWord = "";
        }
    }

    removeThe(arguments);



    return *arguments;
}

