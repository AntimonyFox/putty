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
    ADDARRAY("northeast", northEastAlias);
    ADDARRAY("northwest", northWestAlias);
    ADDARRAY("southeast", southEastAlias);
    ADDARRAY("southwest", southWestAlias);
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
    ADDARRAY("moveobj", moveObjAlias);
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

string Capitalize(string capMe)
{
    if(capMe[0] >= 97 && capMe[0] <= 122)
    {
        capMe[0] -= 32;
    }

    for(unsigned int i = 1 ; i < capMe.length() ; ++i)
    {
        if(capMe[i] >= 65 && capMe[i] <= 90)
        {
            capMe[i] += 32;
        }
    }

    return capMe;
}

void ChatParser::ChatError()
{
    cout << "I don't understand what you are saying." << endl;
}

void ChatParser::NoText()
{
    cout << "You havent typed anything." << endl;
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

    if(arguments->size() > 0)
    {
        string al = aliasMap[ToLower((*arguments)[0])];

        if(al == "")
        {
            ChatError();
        }
        else
        {
            removeThe(arguments);
            if(al == "look")
            {
                if(arguments->size() > 2)
                {
                    if((*arguments)[1] == "at")
                    {
                        Examine((*arguments)[2]);
                    }
                    else
                    {
                        Look();
                    }
                }
                else
                {
                    Look();
                }
            }
            else if(al == "inventory")
            {
                Inventory();
            }
            else if(al == "move")
            {
                if(arguments->size() == 1)
                {
                    cout << Capitalize((*arguments)[0]) << " in what direction?" << endl;
                }
                else
                {
                    Move((*arguments)[1]);
                }
            }
            else if(al == "north")
            {
                Move(al);
            }
            else if(al == "south")
            {
                Move(al);
            }
            else if(al == "west")
            {
                Move(al);
            }
            else if(al == "east")
            {
                Move(al);
            }
            else if(al == "northeast")
            {
                Move(al);
            }
            else if(al == "northwest")
            {
                Move(al);
            }
            else if(al == "southeast")
            {
                Move(al);
            }
            else if(al == "southwest")
            {
                Move(al);
            }
            else if(al == "up")
            {
                Move(al);
            }
            else if(al == "down")
            {
                Move(al);
            }
            else if(al == "use")
            {
                if(arguments->size() > 1)
                {
                    Use((*arguments)[1]);
                }
                else if(arguments->size() > 3 && (*arguments)[2]=="on")
                {
                    Use((*arguments)[1], (*arguments)[3]);
                }
                else
                {
                    cout << "Use what?" << endl;
                }
            }
            else if(al == "drop")
            {
                if(arguments->size() > 1)
                {
                    Drop((*arguments)[1]);
                }
                else
                {
                    cout << "Drop what?" << endl;
                }
            }
            else if(al == "take")
            {
                if(arguments->size() > 1)
                {
                    Take((*arguments)[1]);
                }
                else
                {
                    cout << "Take what?" << endl;
                }
            }
            else if(al == "open")
            {
                if(arguments->size() > 1)
                {
                    Open((*arguments)[1]);
                }
                else
                {
                    cout << "Open what?" << endl;
                }
            }
            else if(al == "read")
            {
                if(arguments->size() > 1)
                {
                    Read((*arguments)[1]);
                }
                else
                {
                    cout << "Read what?" << endl;
                }
            }
            else if(al == "put")
            {
                if(arguments->size() > 1)
                {
                    Open((*arguments)[1]);
                }
                else
                {
                    cout << "Open what?" << endl;
                }
            }
        }

    }
    else
    {
        NoText();
    }

    return *arguments;
}

void ChatParser::Look()
{

}

void ChatParser::Inventory()
{

}

void ChatParser::TakeAll()
{

}

void ChatParser::DropAll()
{

}

void ChatParser::ExamineAll()
{

}

bool ChatParser::Throw(string throwMe, string hitMe)
{

    return true;
}

bool Throw(string throwMe, string hitMe)
{

    return true;
}

bool ChatParser::Move(string dir)
{

    return true;
}

bool ChatParser::Use(string useMe)
{

    return true;
}

bool ChatParser::Use(string useMe, string onMe)
{

    return true;
}

bool ChatParser::Drop(string dropMe)
{

    return true;
}

bool ChatParser::Take(string takeMe)
{

    return true;
}

bool ChatParser::Open(string openMe)
{

    return true;
}

bool ChatParser::Read(string readMe)
{

    return true;
}

bool ChatParser::Put(string putMe, string fillMe)
{

    return true;
}

bool ChatParser::Drink(string drinkMe)
{

    return true;
}

bool ChatParser::Turn(string turnMe, bool on)
{

    return true;
}

bool ChatParser::MoveObj(string moveMe)
{

    return true;
}

bool ChatParser::Attack(string attackMe, string attackWithMe)
{

    return true;
}

bool ChatParser::Examine(string examineMe)
{

    return true;
}

bool ChatParser::Eat(string eatMe)
{

    return true;
}

bool ChatParser::Close(string closeMe)
{

    return true;
}

bool ChatParser::Tie(string tieMe, string toMe)
{

    return true;
}

bool ChatParser::Break(string breakMe, string withMe)
{

    return true;
}

bool ChatParser::Jump()
{

    return true;
}

bool ChatParser::Pray()
{

    return true;
}

bool ChatParser::Diagnose()
{

    return true;
}

bool ChatParser::Shout()
{

    return true;
}

bool ChatParser::Destroy(string destroyMe)
{

    return true;
}

bool ChatParser::Swap(string swapMe, string withMe)
{

    return true;
}

bool ChatParser::LookAt(string lookAtMe)
{

    return true;
}

bool ChatParser::Save(int state)
{

    return true;
}

bool ChatParser::Restore(int state)
{

    return true;
}

