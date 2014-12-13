#include "Game.h"

#include "PuttyParser.h"
#include "ChatParser.h"

#include <thread>

Game::Game(string path)
{
    isLoaded = false;
    PuttyParser::getInstance().Parse(path, this);
}

Game::~Game()
{
    //dtor
}

void Game::Start()
{
    if(isLoaded && !hasError)
    {
        currentRoom = (startingRoom != "") ? rooms[startingRoom] : rooms.begin()->second;

        //TODO: shouldn't be a pointer
        inventory = new Container();

        ChatParser::Init(this);

        cout << ChatParser::Look();

        string uInput;
        while(true)
        {
            cout << endl;
            cout << "> ";
            getline(cin, uInput);
            cout << ChatParser::Parse(uInput);
        }
    }
}

Thing* Game::GetItem(string itemName)
{
    return (things)[itemName];
}

Thing* Game::GetItemInRoom(string itemName)
{
    if (currentRoom->contents.count(itemName))
    {
        return currentRoom->contents[itemName];
    }
    else
    {
        for (auto roomPair : currentRoom->contents)
        {
            Thing *roomThing = roomPair.second;
            if (roomThing->isContainer && roomThing->isOpen)
            {
                for (auto innerPair : roomThing->contents)
                {
                    Thing *innerThing = innerPair.second;
                    if (innerThing->contents.count(itemName))
                    {
                        return innerThing->contents[itemName];
                    }
                }
            }
        }
    }
}
