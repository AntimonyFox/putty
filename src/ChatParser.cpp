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

Game* ChatParser::game;
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

vector<Thing*> ChatParser::DeterminePossibleThings(vector<string> * arguments)
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

bool ChatParser::RoomHasThing(Thing *thing)
{
    shared_ptr<Room> room = game->currentRoom;

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

bool ChatParser::InventoryHasThing(Thing *thing)
{
    if (game->inventory->GetItem(thing->filename)) {
        return true;
    } else {
        for (auto pair : *game->inventory->container) {
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
            for (int i = 1; i < arguments->size(); i++) {
            output += join + (*arguments)[i];
        }
    }
    return output;
}

string ChatParser::Parse(string parseMe)
{
    vector<string> * arguments = StringToArguments(parseMe);
    string al = DetermineCommand(arguments);
    string thingInTheirWords = Implode(arguments, " ");
    vector<Thing*> possThings = DeterminePossibleThings(arguments);
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
        return Look();
    }
    else if(al == "inventory")
    {
        return Inventory();
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
        return Move(al);
    }
    else if(al == "move")
    {
        return Move((*arguments)[0]);
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
        return Drop(thing);
    }
    else if (!RoomHasThing(thing) && !InventoryHasThing(thing))
    {
        return "You can't see any " + thingInTheirWords + " here!\n";
    }
    else if(al == "take")
    {
        return Take(thing);
    }
    else if(al == "examine")
    {
        return Examine(thing);
    }
    else if(al == "open")
    {
        return Open(thing);
    }
    else if(al == "drink")
    {
        return Drink(thing);
    }
    else if(al == "read")
    {
        return Read(thing);
    }
    else if(al == "turn on")
    {
        return Turn(thing, true);
    }
    else if(al == "turn off")
    {
        return Turn(thing, false);
    }
    else if(al == "moveobj")
    {
        return MoveObj(thing);
    }
    else if(al == "eat")
    {
        return Eat(thing);
    }
    else if(al == "close")
    {
        return Close(thing);
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

string ChatParser::Look()
{
    return game->currentRoom->look();
}

string ChatParser::Inventory()
{
    if (!game->inventory->IsEmpty())
        return game->inventory->printContainer();
    else
        return "You are empty-handed.\n";
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
    //copy item as temp (for room)
    //Thing temp = throwMe;
    Thing* temp = game->inventory->GetItem(throwMe);
    //remove item from Inventory
    game->inventory->remove(throwMe, 1);

    //check if breakable
    if(temp->isBreakable == true){
    //if true - do nothing!
        cout << "it's broke, don't throw! Bahahahahahahaha" << endl;
        return false;
    }
    //if false - add copy to room
    else{
        cout << "You throw the " << throwMe << " at the " << hitMe << "." << endl;
        game->currentRoom->contents[throwMe] = temp;
        return true;
    }
    return true;
}

string ChatParser::Move(string dir)
{
    shared_ptr<Room> room(game->currentRoom);
    if (dir == "north" && room->north) {
        game->currentRoom = room->north;
    } else if (dir == "south" && room->south) {
        game->currentRoom = room->south;
    } else if (dir == "west" && room->west) {
        game->currentRoom = room->west;
    } else if (dir == "east" && room->east) {
        game->currentRoom = room->east;
    } else if (dir == "up" && room->up) {
        game->currentRoom = room->up;
    } else if (dir == "down" && room->down) {
        game->currentRoom = room->down;
    } else {
        return "You can't go that way.\n";
    }

    return game->currentRoom->look();
}

bool ChatParser::Use(string useMe)
{
    Thing* temp = game->inventory->GetItem(useMe);

    if (temp != nullptr)
    {
        game->inventory->useItem(useMe);
        cout << "You used: " << useMe << "!" << endl;
    }
    else
    {
        cout << "You don't have the " << useMe << "." << endl;
    }
    return true;
}

bool ChatParser::Use(string useMe, string onMe)
{

    return true;
}

string ChatParser::Drop(Thing *dropMe)
{
    if (game->inventory->GetItem(dropMe->filename)) {
        game->inventory->remove(dropMe->filename, 1);
        game->currentRoom->contents[dropMe->filename] = dropMe;
        return "Dropped.\n";
    } else {
        return "You don't have that!\n";
    }
}

string ChatParser::Take(Thing *takeMe)
{
    if (InventoryHasThing(takeMe))
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
        shared_ptr<Room> room = game->currentRoom;
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
                    if (innerPair.second == takeMe)
                    {
                        roomThing->contents.erase(takeMe->filename);
                        break;
                    }
                }
            }
        }
        game->inventory->add(takeMe);
        return "Taken.\n";
    }
}

string ChatParser::Open(Thing *openMe)
{
    shared_ptr<Room> room = game->currentRoom;

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

string ChatParser::Read(Thing *readMe)
{
    string output = "";
    if (readMe->isReadable) {
        if (!InventoryHasThing(readMe)) {
            Take(readMe);
            if (InventoryHasThing(readMe)) {
                output += "(Taken).\n";
            }
        }
        output += readMe->description + "\n";
    } else {
        output += "How does one read a " + readMe->GetName() + "?\n";
    }
    return output;
}

bool ChatParser::Put(string putMe, string fillMe)
{
    auto* tempPut = game->inventory->GetItem(putMe);
    auto* tempFill = game->currentRoom->contents[fillMe];

    if(tempFill->isContainer){
            if(!tempFill->isOpen){
                tempFill->isOpen = true;
                if(tempFill->capacity >= tempPut->size){
                    tempFill->contents[fillMe] = tempPut;
                    game->inventory->remove(putMe, 1);
                }
                else{
                    cout << fillMe << "does not have enough room" << endl;
                }
            }
    }
    return true;
}

string ChatParser::Drink(Thing *drinkMe)
{
    if (!drinkMe->isDrinkable) {
        return "I don't think the " + drinkMe->GetName() + " would agree with you.\n";
    } else {
        for (auto pair : *game->inventory->container) {
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
        for (auto pair : game->currentRoom->contents) {
            Thing *pairThing = pair.second;
            for (auto innerPair : pairThing->contents) {
                Thing *innerThing = innerPair.second;
                if (innerThing == drinkMe) {
                    return "You have to be holding the " + pairThing->GetName() + " first.\n";
                }
            }
        }
    }
}

string ChatParser::Turn(Thing *turnMe, bool on)
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
}

bool ChatParser::Turn(string turnMe)
{

    return true;
}

string ChatParser::MoveObj(Thing *moveMe)
{
    if (InventoryHasThing(moveMe)) {
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

bool ChatParser::Attack(string attackMe, string attackWithMe)
{

    return true;
}

string ChatParser::Examine(Thing *examineMe)
{
    return examineMe->Look();
}

string ChatParser::Eat(Thing *eatMe)
{
    if (!eatMe->isEdible) {
        return "I don't think the " + eatMe->GetName() + " would agree with you.\n";
    } else {
        for (auto pair : *game->inventory->container) {
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
        for (auto pair : game->currentRoom->contents) {
            Thing *pairThing = pair.second;
            for (auto innerPair : pairThing->contents) {
                Thing *innerThing = innerPair.second;
                if (innerThing == eatMe) {
                    return "You have to be holding the " + pairThing->GetName() + " first.\n";
                }
            }
        }
    }
}

string ChatParser::Close(Thing *closeMe)
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

