#include "ChatParser.h"

#define ADDARRAY(str, arr) for(unsigned int i = 0 ; i < ( sizeof(arr)/sizeof(arr[0]) ) ; ++i){aliasMap[arr[i]] = str;}

string ChatParser::lookAlias[3] = {"look", "l", "description"};
string ChatParser::inventoryAlias[3] = {"inventory", "i", "inv"};

string ChatParser::moveAlias[3] = {"go", "walk", "run"};
string ChatParser::northAlias[2] = {"north", "n"};
string ChatParser::eastAlias[2] = {"east", "e"};
string ChatParser::southAlias[2] = {"south", "s"};
string ChatParser::westAlias[2] = {"west","w"};
string ChatParser::northEastAlias[2] = {"northeast", "ne"};
string ChatParser::northWestAlias[2] = {"northwest", "nw"};
string ChatParser::southEastAlias[2] = {"southeast", "se"};
string ChatParser::southWestAlias[2] = {"southwest", "sw"};
string ChatParser::upAlias[1] = {"up"};
string ChatParser::downAlias[1] = {"down"};
string ChatParser::throwAlias[2] = {"throw", "toss"};
string ChatParser::useAlias[2] = {"use", "u"};
string ChatParser::dropAlias[3] = {"drop", "unhand", "d"};
string ChatParser::takeAlias[4] = {"take", "get", "grab", "t"};
string ChatParser::openAlias[2] = {"open", "o"};
string ChatParser::readAlias[1] = {"read"};
string ChatParser::putAlias[3] = {"put", "place", "set"};
string ChatParser::drinkAlias[2] = {"drink", "swallow"};
string ChatParser::turnAlias[2] = {"turn", "switch"};
string ChatParser::moveObjAlias[2] = {"move", "push"};
string ChatParser::attackAlias[4] = {"attack", "kill", "sick", "swing at"};
string ChatParser::examineAlias[2] = {"examine", "look at"};
string ChatParser::eatAlias[2] = {"eat", "consume"};
string ChatParser::closeAlias[2] = {"close", "c"};
string ChatParser::tieAlias[4] = {"tie", "fasten", "attach", "join"};
string ChatParser::breakAlias[2] = {"break", "destroy"};
string ChatParser::jumpAlias[2] = {"jump", "hop"};
string ChatParser::prayAlias[1] = {"pray"};
string ChatParser::shoutAlias[3] = {"shout", "yell", "bark"};
string ChatParser::diagnoseAlias[2] = {"diagnose", "health"};
string ChatParser::saveAlias[1] = {"save"};
string ChatParser::restoreAlias[2] = {"restore", "load"};

map<string, string> ChatParser::aliasMap = map<string, string>();

void ChatParser::Init()
{
    ADDARRAY("look", lookAlias);
    ADDARRAY("inventory", inventoryAlias);
    ADDARRAY("move", moveAlias);
    ADDARRAY("north", northAlias);
    ADDARRAY("east", eastAlias);
    ADDARRAY("south", southAlias);
    ADDARRAY("west", westAlias);
    ADDARRAY("northEast", northEastAlias);
    ADDARRAY("northWest", northWestAlias);
    ADDARRAY("southEast", southEastAlias);
    ADDARRAY("southWest", southWestAlias);
    ADDARRAY("up", upAlias);
    ADDARRAY("down", downAlias);
    ADDARRAY("throw", throwAlias);
    ADDARRAY("use", useAlias);
    ADDARRAY("drop ", dropAlias);
    ADDARRAY("take", takeAlias);
    ADDARRAY("open", openAlias);
    ADDARRAY("read", readAlias);
    ADDARRAY("put", putAlias);
    ADDARRAY("drink", drinkAlias);
    ADDARRAY("turn", turnAlias);
    ADDARRAY("moveObj", moveObjAlias);
    ADDARRAY("attack", attackAlias);
    ADDARRAY("eat", eatAlias);
    ADDARRAY("close", closeAlias);
    ADDARRAY("tie", tieAlias);
    ADDARRAY("break", breakAlias);
    ADDARRAY("jump", jumpAlias);
    ADDARRAY("pray", prayAlias);
    ADDARRAY("shout", shoutAlias);
    ADDARRAY("diagnose", diagnoseAlias);
    ADDARRAY("save", saveAlias);
    ADDARRAY("restore", restoreAlias);

}

string ToLower(string lowerMe)
{
    for(unsigned int i = 0 ; i < lowerMe.length() ; ++i)
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

    cout << aliasMap[(*arguments)[0]] << endl;

    return *arguments;
}

