#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Thing.h"
#include "Container.h"

#include <mutex>
#include <map>

class Player
{
    public:
    shared_ptr<Room> currentRoom;
    Container *inventory;
};

using namespace std;

class Game
{
    friend class PuttyParser;
    friend class ChatParser;

    public:
        Game(string path);
        virtual ~Game();
        void Start();

    private:
        //Static
        string startingRoom;
        map<string, shared_ptr<Room>> rooms;
        map<string, Thing*> things;
        mutex ipMutex;


        //Dynamic
        Container *inventory;
        shared_ptr<Room> currentRoom;
        bool isLoaded;
        bool hasError;
        map<string, Player*> ipMap;

        //Functions
        Thing *GetItem(string itemName);
        Thing *GetItemInRoom(string itemName);
        Player* CreatePlayer(string ip);
        Player* GetPlayer(string ip);

};

#endif // GAME_H
