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
string ChatParser::inAlias[3] = {"in", "into", "enter"};

map<string, string> ChatParser::aliasMap = map<string, string>();
mutex ChatParser::cMutex;
vector<thread> ChatParser::threadList = vector<thread>();
Game* ChatParser::game;
string ChatParser::port = DEFAULT_PORT;

bool isNumber(string check)
{
    for (unsigned int i = 0; i < check.size(); ++i)
    {
        if (check[i] < '0' && check[i] > '9')
            return false;
    }
    return true;
}

void ChatParser::Init(Game *game)
{
    ChatParser::game = game;

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
    ADDARRAY("drop", dropAlias);
    ADDARRAY("take", takeAlias);
    ADDARRAY("open", openAlias);
    ADDARRAY("read", readAlias);
    ADDARRAY("put", putAlias);
    ADDARRAY("drink", drinkAlias);
    ADDARRAY("turn", turnAlias);
    ADDARRAY("moveobj", moveObjAlias);
    ADDARRAY("attack", attackAlias);
    ADDARRAY("examine", examineAlias);
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
    ADDARRAY("in", inAlias);

    do {
        cout << "Port: ";
        getline(cin, port);
    } while (!isNumber(port));

    StartServer();
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

string RemoveSpaces(string changeMe)
{
    string returnMe = "";

    for(unsigned int i = 0 ; i < changeMe.length() ; ++i)
    {
        if((changeMe[i] >= 65 && changeMe[i] <= 90) || (changeMe[i] >= 97 && changeMe[i] <= 122))
        {
            returnMe += changeMe[i];
        }
    }

    return returnMe;
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

string ChatParser::ChatError()
{
    return "I don't understand what you are saying.\n";
}

string ChatParser::NoText()
{
    return "You haven't typed anything.\n";
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

void removeFirst(vector<string> * purgeMe)
{
    purgeMe->erase(purgeMe->begin());
}

vector<string> * StringToArguments(string parseMe)
{
    vector<string> * arguments = new vector<string>();
    string curWord = "";
    for(unsigned int i = 0 ; i < parseMe.length() ; ++i)
    {
        char curChar = parseMe[i];
        if(curChar != ' ')
            curWord += curChar;
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
    return arguments;
}

string ChatParser::DetermineCommand(vector<string> * arguments)
{
    if(arguments->size() > 0)
    {
        string al = aliasMap[ToLower((*arguments)[0])];
        if (al == "")
        {
            return "";
        }
        removeThe(arguments);
        removeFirst(arguments);
        if(al == "look")
        {
            if(arguments->size() > 1 && (*arguments)[0] == "at") {
                removeFirst(arguments);
                return "examine";
            }
        }
        else if (al == "move")
        {
            string bl = (*arguments)[0];
            if (arguments->size() > 0 && (
                                         bl == "north" ||
                                         bl == "south" ||
                                         bl == "east" ||
                                         bl == "west" ||
                                         bl == "northeast" ||
                                         bl == "northwest" ||
                                         bl == "southeast" ||
                                         bl == "southwest" ||
                                         bl == "up" ||
                                         bl == "down"))
            {
                return "move";
            }
            else
            {
                return "moveObj";
            }
        }
        else if (al == "turn")
        {
            string bl = (*arguments)[0];
            if (bl == "on" || bl == "off") {
                removeFirst(arguments);
                return "turn " + bl;
            }
        }
        return al;
//        else if(al == "use")
//        {
//            if(arguments->size() > 0)
//            {
//                Use((*arguments)[0]);
//            }
//            else if(arguments->size() > 3 && (*arguments)[1]=="on")
//            {
//                Use((*arguments)[0], (*arguments)[2]);
//            }
//        }
//        else if(al == "throw")
//        {
//            if(arguments->size() > 2 && ToLower((*arguments)[1]) == "at")
//            {
//                Throw((*arguments)[0], (*arguments)[2]);
//            }
//            else
//            {
//                ChatError();
//            }
//        }
//        else if(al == "put")
//        {
//            if(arguments->size() > 2 && ToLower((*arguments)[1]) == "in")
//            {
//                Put((*arguments)[0], (*arguments)[2]);
//            }
//            else
//            {
//                ChatError();
//            }
//        }
//        else if(al == "attack")
//        {
//            if(arguments->size() > 2 && ToLower((*arguments)[1]) == "with")
//            {
//                Attack((*arguments)[0], (*arguments)[2]);
//            }
//            else
//            {
//                ChatError();
//            }
//        }
//        else if(al == "tie")
//        {
//            if(arguments->size() > 2 && ToLower((*arguments)[1]) == "with")
//            {
//                Tie((*arguments)[0], (*arguments)[2]);
//            }
//            else
//            {
//                ChatError();
//            }
//        }
//        else if(al == "break")
//        {
//            if(arguments->size() > 2 && ToLower((*arguments)[1]) == "with")
//            {
//                Break((*arguments)[0], (*arguments)[2]);
//            }
//            else
//            {
//                ChatError();
//            }
//        }
//        else if(al == "swap")
//        {
//            if(arguments->size() > 2 && ToLower((*arguments)[1]) == "with")
//            {
//                Swap((*arguments)[0], (*arguments)[2]);
//            }
//            else
//            {
//                ChatError();
//            }
//        }
    }
    else
    {
        return "";
    }
}

bool IsPossibleThing(Thing *thing, vector<string> * arguments)
{
    bool isPossibleThing = true;
    vector<string> keywords = thing->keywords;
    if (!keywords.empty()) {
        for (string arg : *arguments) {
            bool isKeyword = false;
            for (string keyword : keywords) {
                if (arg == keyword) {
                    isKeyword = true;
                    break;
                }
            }
            if (!isKeyword) {
                isPossibleThing = false;
                break;
            }
        }
    } else {
        isPossibleThing = false;
    }
    return isPossibleThing;
}

vector<Thing*> ChatParser::DeterminePossibleThings(Player* p, vector<string> * arguments)
{
    vector<Thing*> possThings;
    if (!arguments->empty()) {
        for (auto roomPair : game->things) {
            Thing *roomThing = roomPair.second;
            if (IsPossibleThing(roomThing, arguments)) {
                possThings.push_back(roomThing);
            }
        }
    }
    return possThings;
}

bool ChatParser::RoomHasThing(Player* p, Thing *thing)
{
    shared_ptr<Room> room = p->currentRoom;

    for (auto roomPair : room->contents) {
        Thing *roomThing = roomPair.second;
        if (thing == roomThing) {
            return true;
        } else if (roomThing->isContainer && roomThing->isOpen && !roomThing->contents.empty()) {
            for (auto innerPair : roomThing->contents) {
                Thing *innerThing = innerPair.second;
                if (thing == innerThing) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChatParser::InventoryHasThing(Player* p, Thing *thing)
{
    if (p->inventory->GetItem(thing->filename)) {
        return true;
    } else {
        for (auto pair : *p->inventory->container) {
            Thing *invThing = pair.second.item;
            for (auto innerPair : invThing->contents) {
                Thing *innerThing = innerPair.second;
                if (innerThing == thing) {
                    return true;
                }
            }
        }
    }
    return false;
}

string Implode(vector<string> * arguments, string join)
{
    string output = "";
    if (!arguments->empty()) {
        output += (*arguments)[0];
            for (unsigned int i = 1; i < arguments->size(); i++) {
            output += join + (*arguments)[i];
        }
    }
    return output;
}

string ChatParser::Parse(string parseMe, Player* p)
{
    vector<string> * arguments = StringToArguments(parseMe);
    cout << parseMe << endl;
    string al = DetermineCommand(arguments);
    string thingInTheirWords = Implode(arguments, " ");
    vector<Thing*> possThings = DeterminePossibleThings(p, arguments);
    Thing *thing = !possThings.empty() ? possThings.front() : nullptr;

    if(parseMe == "")
    {
        return NoText();
    }
    else if(al == "")
    {
        return ChatError();
    }
    else if(al == "look")
    {
        return Look(p);
    }
    else if(al == "inventory")
    {
        return Inventory(p);
    }
    else if(
            al == "north" ||
            al == "south" ||
            al == "west" ||
            al == "east" ||
            al == "northeast" ||
            al == "northwest" ||
            al == "southeast" ||
            al == "southwest" ||
            al == "up" ||
            al == "down")
    {
        return Move(p, al);
    }
    else if(al == "move")
    {
        return Move(p, (*arguments)[0]);
    }
    else if(al == "pray")
    {
        return Pray();
    }
    else if(al == "jump")
    {
        return Jump();
    }
    else if(al == "diagnose")
    {
        return Diagnose();
    }
    else if(al == "shout")
    {
        return Shout();
    }
    else if(arguments->empty())
    {
        return "What do you want to " + al + "?\n";
    }
    else if (possThings.empty())
    {
        return "I'm not sure exactly what you're talking about.\n";
    }
    else if (possThings.size() > 1)
    {
        return "You're going to need to be a little more specific.\n";
    }
    //Must be holding item
    else if(al == "drop")
    {
        return Drop(p, thing);
    }
    else if (!RoomHasThing(p, thing) && !InventoryHasThing(p, thing))
    {
        return "You can't see any " + thingInTheirWords + " here!\n";
    }
    else if(al == "take")
    {
        return Take(p, thing);
    }
    else if(al == "examine")
    {
        return Examine(p, thing);
    }
    else if(al == "open")
    {
        return Open(p, thing);
    }
    else if(al == "drink")
    {
        return Drink(p, thing);
    }
    else if(al == "read")
    {
        return Read(p, thing);
    }
    else if(al == "turn on")
    {
        return Turn(p, thing, true);
    }
    else if(al == "turn off")
    {
        return Turn(p, thing, false);
    }
    else if(al == "moveobj")
    {
        return MoveObj(p, thing);
    }
    else if(al == "eat")
    {
        return Eat(p, thing);
    }
    else if(al == "close")
    {
        return Close(p, thing);
    }
    else if(al == "in")
    {
        return In(p, thing);
    }
//    else if(al == "destroy")
//    {
//        if(arguments->size() > 0)
//        {
//            Destroy((*arguments)[0]);
//        }
//    }
//    else if(al == "save")
//    {
//        if(arguments->size() > 0)
//        {
//            Save((*arguments)[0]);
//        }
//    }
//    else if(al == "restore")
//    {
//        if(arguments->size() > 0)
//        {
//            Restore((*arguments)[0]);
//        }
//    }
    else
    {
        //Gets here if there's an alias but no implementation
        return "Unknown command: " + al + ".\n";
    }
    return "";
}

string ChatParser::Look(Player* p)
{
    return p->currentRoom->look();
}

string ChatParser::Inventory(Player* p)
{
    if (!p->inventory->IsEmpty())
        return p->inventory->printContainer();
    else
        return "You are empty-handed.\n";
}

void ChatParser::TakeAll(Player* p)
{

}

void ChatParser::DropAll(Player* p)
{

}

void ChatParser::ExamineAll(Player* p)
{

}

bool ChatParser::Throw(Player* p, string throwMe, string hitMe)
{
    //copy item as temp (for room)
    //Thing temp = throwMe;
    Thing* temp = p->inventory->GetItem(throwMe);
    //remove item from Inventory
    p->inventory->remove(throwMe, 1);

    //check if breakable
    if(temp->isBreakable == true){
    //if true - do nothing!
        cout << "it's broke, don't throw! Bahahahahahahaha" << endl;
        return false;
    }
    //if false - add copy to room
    else{
        cout << "You throw the " << throwMe << " at the " << hitMe << "." << endl;
        p->currentRoom->contents[throwMe] = temp;
        return true;
    }
    return true;
}

string ChatParser::Move(Player* p, string dir)
{
    shared_ptr<Room> room(p->currentRoom);

    if (dir == "north" && room->north) {
        p->currentRoom = room->north;
    } else if (dir == "south" && room->south) {
        p->currentRoom = room->south;
    } else if (dir == "west" && room->west) {
        p->currentRoom = room->west;
    } else if (dir == "east" && room->east) {
        p->currentRoom = room->east;
    } else if (dir == "up" && room->up) {
        p->currentRoom = room->up;
    } else if (dir == "down" && room->down) {
        p->currentRoom = room->down;
    } else {
        return "You can't go that way.\n";
    }

    {
        room->players.erase(p->name);
        p->currentRoom->players[p->name] = p;
    }

    return p->currentRoom->look();
}

bool ChatParser::Use(Player* p, string useMe)
{
    Thing* temp = p->inventory->GetItem(useMe);

    if (temp != nullptr)
    {
        p->inventory->useItem(useMe);
        cout << "You used: " << useMe << "!" << endl;
    }
    else
    {
        cout << "You don't have the " << useMe << "." << endl;
    }
    return true;
}

bool ChatParser::Use(Player* p, string useMe, string onMe)
{

    return true;
}

string ChatParser::Drop(Player* p, Thing *dropMe)
{
    if (p->inventory->GetItem(dropMe->filename)) {
        p->inventory->remove(dropMe->filename, 1);
        p->currentRoom->contents[dropMe->filename] = dropMe;
        return "Dropped.\n";
    } else {
        return "You don't have that!\n";
    }
}

string ChatParser::Take(Player* p, Thing *takeMe)
{
    if (InventoryHasThing(p, takeMe))
    {
        return "You already have that!\n";
    }
    else if (takeMe->isAnchored)
    {
        return "It is securely anchored.\n";
    }
    else if (!takeMe->isFree)
    {
        return "An interesting idea...\n";
    }
    else
    {
        shared_ptr<Room> room = p->currentRoom;
        for (auto roomPair : room->contents)
        {
            Thing *roomThing = roomPair.second;
            if (roomPair.second == takeMe)
            {
                room->contents.erase(takeMe->filename);
                break;
            }
            else if (roomThing->isContainer && roomThing->isOpen && !roomThing->contents.empty())
            {
                for (auto innerPair : roomThing->contents)
                {
                    Thing *innerThing = innerPair.second;
                    if (innerThing == takeMe)
                    {
                        roomThing->contents.erase(takeMe->filename);
                        break;
                    }
                }
            }
        }
        p->inventory->add(takeMe);
        return "Taken.\n";
    }
}

string ChatParser::Open(Player* p, Thing *openMe)
{
    shared_ptr<Room> room = p->currentRoom;

    if (openMe->isContainer)
    {
        if (!openMe->isOpen)
        {
            openMe->isOpen = true;
            if (!openMe->contents.empty())
            {
                string output = "";
                output += "Opening the " + openMe->name + " reveals ";
                string list;
                for (auto content = openMe->contents.begin(); content != openMe->contents.end(); ++content)
                {
                    if (list != "")
                    {
                        list += ", ";
                        if (content == --openMe->contents.end())
                            list += "and ";
                    }
                    list += content->second->ArticleName();
                }
                output += list + ".\n";
                return output;
            }
            else
            {
                return "Opened.\n";
            }
        }
        else
        {
            return "It is already open.\n";
        }
    } else {
        return "You must tell me how to do that to " + openMe->ArticleName () + ".\n";
    }
}

string ChatParser::Read(Player* p, Thing *readMe)
{
    string output = "";
    if (readMe->isReadable) {
        if (!InventoryHasThing(p, readMe)) {
            Take(p, readMe);
            if (InventoryHasThing(p, readMe)) {
                output += "(Taken).\n";
            }
        }
        output += readMe->description + "\n";
    } else {
        output += "How does one read a " + readMe->GetName() + "?\n";
    }
    return output;
}

bool ChatParser::Put(Player* p, string putMe, string fillMe)
{
    auto* tempPut = p->inventory->GetItem(putMe);
    auto* tempFill = p->currentRoom->contents[fillMe];

    if(tempFill->isContainer){
            if(!tempFill->isOpen){
                tempFill->isOpen = true;
                if(tempFill->capacity >= tempPut->size){
                    tempFill->contents[fillMe] = tempPut;
                    p->inventory->remove(putMe, 1);
                }
                else{
                    cout << fillMe << "does not have enough room" << endl;
                }
            }
    }
    return true;
}

string ChatParser::Drink(Player* p, Thing *drinkMe)
{
    if (!drinkMe->isDrinkable) {
        return "I don't think the " + drinkMe->GetName() + " would agree with you.\n";
    } else {
        for (auto pair : *p->inventory->container) {
            Thing *pairThing = pair.second.item;
            for (auto innerPair : pairThing->contents) {
                Thing *innerThing = innerPair.second;
                if (innerThing == drinkMe) {
                    if (!pairThing->isOpen) {
                        return "You'll have to open the " + pairThing->GetName() + " first.\n";
                    } else {
                        pairThing->contents.erase(drinkMe->filename);
                        return "Thank you very much. I was rather thirsty (from all this talking, probably).\n";
                    }
                }
            }
        }
        for (auto pair : p->currentRoom->contents) {
            Thing *pairThing = pair.second;
            for (auto innerPair : pairThing->contents) {
                Thing *innerThing = innerPair.second;
                if (innerThing == drinkMe) {
                    return "You have to be holding the " + pairThing->GetName() + " first.\n";
                }
            }
        }
    }
    return "";
}

string ChatParser::Turn(Player* p, Thing *turnMe, bool on)
{
    if (turnMe->isToggleable) {
        if (on && turnMe->isOn) {
            return "It is already on.\n";
        } else if (!on && !turnMe->isOn) {
            return "It is already off.\n";
        } else {
            turnMe->isOn = on;
            return "The " + turnMe->GetName() + " is now " + (on ? "on" : "off") + ".\n";
        }
    }
    return "";
}

bool ChatParser::Turn(Player* p, string turnMe)
{

    return true;
}

string ChatParser::MoveObj(Player* p, Thing *moveMe)
{
    if (InventoryHasThing(p, moveMe)) {
        return "You're not an accomplished enough juggler.\n";
    } else if (!moveMe->isMovable) {
        return "You can't move the " + moveMe->GetName() + ".\n";
    } else if (moveMe->isMoved) {
        return "You've already moved the " + moveMe->GetName() + ".\n";
    } else {
        if (moveMe->hides) {
            moveMe->isMoved = true;
            return "Moving the " + moveMe->GetName() + " reveals " + moveMe->hides->ArticleName() + ".\n";
        } else {
            return "Moving the " + moveMe->GetName() + " reveals nothing.\n";
        }
    }
}

bool ChatParser::Attack(Player* p, string attackMe, string attackWithMe)
{

    return true;
}

string ChatParser::Examine(Player* p, Thing *examineMe)
{
    return examineMe->Look();
}

string ChatParser::Eat(Player* p, Thing *eatMe)
{
    if (!eatMe->isEdible) {
        return "I don't think the " + eatMe->GetName() + " would agree with you.\n";
    } else {
        for (auto pair : *p->inventory->container) {
            Thing *pairThing = pair.second.item;
            for (auto innerPair : pairThing->contents) {
                Thing *innerThing = innerPair.second;
                if (innerThing == eatMe) {
                    if (!pairThing->isOpen) {
                        return "You'll have to open the " + pairThing->GetName() + " first.\n";
                    } else {
                        pairThing->contents.erase(eatMe->filename);
                        return "Thank you very much. I was rather thirsty (from all this talking, probably).\n";
                    }
                }
            }
        }
        return "";
    }
}

string ChatParser::Close(Player* p, Thing *closeMe)
{
    if (closeMe->isContainer) {
        if (closeMe->isOpen) {
            closeMe->isOpen = false;
            return "Closed.\n";
        } else {
            return "It is already closed.\n";
        }
    } else {
        return "You must tell me how to do that to " + closeMe->ArticleName () + ".\n";
    }
}

bool ChatParser::Tie(string tieMe, string toMe)
{

    return true;
}

bool ChatParser::Break(string breakMe, string withMe)
{

    return true;
}

string ChatParser::Jump()
{
    return "Are you enjoying yourself?\n";
}

string ChatParser::Pray()
{
    return "If you pray enough, your prayers may be answered.\n";
}

string ChatParser::Diagnose()
{
    return "Lookin' good.\n";
}

string ChatParser::Shout()
{
    return "Aaaarrrrgggghhhh!\n";
}

bool ChatParser::Destroy(string destroyMe)
{

    return true;
}

bool ChatParser::Swap(string swapMe, string withMe)
{

    return true;
}

bool ChatParser::Save(string state)
{

    return true;
}

bool ChatParser::Restore(string state)
{

    return true;
}

string ChatParser::In(Player *p, Thing *inMe)
{
    if (inMe->enter) {
        p->currentRoom = inMe->enter;
        return Look(p);
    } else {
        return "You can't go that way.\n";
    }
}

string ChatParser::ProcessCommand(string data, Player* p)
{
    unique_lock<mutex> lk(cMutex);


    return Parse(data, p);
}



void ChatParser::ClientThread(SOCKET cSock, char* ip)
{
    int iResult = 0;
    char sendbuf[DEFAULT_BUFLEN] = {0};
    char recvbuf[DEFAULT_BUFLEN] = {0};
    Player* myPlayer;

    string sendString = "What is your username? ";

    for(;;)
    {
        strcpy(sendbuf, sendString.c_str());
        send( cSock, sendbuf, sizeof(sendbuf), 0 );

        iResult = recv(cSock, recvbuf, DEFAULT_BUFLEN, 0);
        printf("Bytes received: %d\n", iResult);

        if(RemoveSpaces(recvbuf) == "")
        {
            sendString = "You did not type anything.";
            continue;
        }

        if((myPlayer = game->GetPlayer((recvbuf))) == NULL)
        {
            myPlayer = game->CreatePlayer((recvbuf));
            sendString = "That username does not exist. Welcome " + string(recvbuf) + "!\n";
            break;
        }
        else
        {
            unique_lock<mutex> lk(cMutex);
            if(myPlayer->inUse == true)
            {
                myPlayer->inUse = true;
                sendString = "That username is already being used.";
                continue;
            }
            else
            {
                sendString = "Welcome " + string(recvbuf) + "!\n";
                break;
            }
            lk.unlock();
        }
    }

    {
        unique_lock<mutex> lk(cMutex);
        myPlayer->currentRoom->players[myPlayer->name] = myPlayer;
    }

    sendString += ProcessCommand("look", myPlayer);
    strcpy(sendbuf, sendString.c_str());
    send( cSock, sendbuf, sizeof(sendbuf), 0 );

    do {
        char recvbuf[DEFAULT_BUFLEN] = {0};
        char sendbuf[DEFAULT_BUFLEN] = {0};

        iResult = recv(cSock, recvbuf, DEFAULT_BUFLEN, 0);

        if (iResult > 0)
        {
            printf("Bytes received: %d\n", iResult);

            strcpy(sendbuf, ProcessCommand(recvbuf, myPlayer).c_str());

            send( cSock, sendbuf, sizeof(sendbuf), 0 );
        }
        else
        {
            printf("Lost Client\n");
            unique_lock<mutex> lk(cMutex);
            LogOff(myPlayer);
            closesocket(cSock);
            lk.unlock();
            break;
        }

    } while (iResult > 0);
}

void ChatParser::LogOff(Player *p)
{
    p->inUse = false;
    p->currentRoom->players.erase(p->name);
}

int ChatParser::StartServer()
{

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;
    struct sockaddr_storage Addr;

    int AddrLen;
    char AddrName[NI_MAXHOST];

    int curID = 0;


    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
        {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    cout << "Server started on port " << port << "!" << endl;

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    for(;;)
    {
        ClientSocket = accept(ListenSocket, NULL, NULL);

        if (ClientSocket != INVALID_SOCKET)
        {
            printf("Client Found! ");
            send( ClientSocket, "sdas", iResult, 0 );

            getpeername(ClientSocket, (LPSOCKADDR)&Addr, &AddrLen);
            getnameinfo((LPSOCKADDR)&Addr, AddrLen, AddrName, sizeof(AddrName), NULL, 0, NI_NUMERICHOST);
            cout << "IP: " << AddrName << endl;
            threadList.push_back(thread(ClientThread, ClientSocket, AddrName) );
        }
    }

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}

