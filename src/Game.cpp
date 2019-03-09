#include "Game.h"

#include <thread>

#include "ChatParser.h"
#include "PuttyParser.h"
#include "utilities.h"

Game::Game(string path) {
    isLoaded = false;
    PuttyParser::getInstance().Parse(path, this);
}

Game::~Game() {
    //dtor
}

Player* Game::CreatePlayer(string username) {
    Player* p = new Player();

    p->inventory = new Container();
    p->currentRoom = (startingRoom != "") ? rooms[startingRoom] : rooms.begin()->second;
    p->inUse = true;
    p->name = username;

    playerMap[ToLower(username)] = p;

    cout << "Player Created with key: " << ToLower(username) << endl;

    return p;
}

Player* Game::GetPlayer(string username) {
    unique_lock<mutex> lk(ipMutex);

    // Get player by Username
    string lowerUsername = ToLower(username);
    auto it = playerMap.find(lowerUsername);

    // If player exists in player map already
    if (it != playerMap.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

bool Game::DestroyPlayer(string username) {
    unique_lock<mutex> lk(ipMutex);

    if (playerMap.find(username) != playerMap.end()) {
        playerMap.erase(username);
        cout << "Destroyed player with username " << username << "." << endl;
        return true;
    } else {
        cout << "Couldn't destroy player with username " << username << " - player not found." << endl;
        return false;
    }
}

void Game::Start() {
    if(isLoaded && !hasError) {
        currentRoom = (startingRoom != "") ? rooms[startingRoom] : rooms.begin()->second;
        playerMap = map<string, Player*>();

        //TODO: shouldn't be a pointer
        inventory = new Container();

        ChatParser::Init(this);

        /*cout << ChatParser::Look();

        string uInput;

        thread t1(update);

        while(true) {
            cout << endl;
            cout << "> ";
            getline(cin, uInput);
            cout << ChatParser::Parse(uInput);
        }*/
    }
}

Thing* Game::GetItem(string itemName) {
    return (things)[itemName];
}

Thing* Game::GetItemInRoom(string itemName) {
    if (currentRoom->contents.count(itemName)) {
        return currentRoom->contents[itemName];
    } else {
        for (auto roomPair : currentRoom->contents) {
            Thing *roomThing = roomPair.second;
            if (roomThing->isContainer && roomThing->isOpen) {
                for (auto innerPair : roomThing->contents) {
                    Thing *innerThing = innerPair.second;
                    if (innerThing->contents.count(itemName)) {
                        return innerThing->contents[itemName];
                    }
                }
            }
        }
        // TODO: Safe?
        return nullptr;
    }
}

void Game::update() {
    for (auto timer: timers)
        timer.update();

    for (auto room: rooms)
        room.second->update();
}

void Game::LostGame() {

}
