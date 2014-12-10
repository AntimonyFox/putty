#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Thing.h"
#include "Container.h"

#include <map>

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

        //Dynamic
        Container *inventory;
        shared_ptr<Room> currentRoom;
        bool isLoaded;

        //Functions
        Thing *GetItem(string itemName);
        Thing *GetItemInRoom(string itemName);
};

#endif // GAME_H
