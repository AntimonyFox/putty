#include "Game.h"

#include "PuttyParser.h"
#include "ChatParser.h"

#include <thread>

Game::Game(string path)
{
    PuttyParser::getInstance().Parse(path, this);
}

Game::~Game()
{
    //dtor
}

void Game::Start()
{
    currentRoom = (startingRoom != "") ? rooms[startingRoom] : rooms.begin()->second;
    inventory = new Inventory();

    ChatParser::Init(this);

    ChatParser::Look();

    string uInput;
    while(true)
    {
        cout << "> ";
        getline(cin, uInput);
        ChatParser::Parse(uInput);
    }
}
