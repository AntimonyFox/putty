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
        map<string, Room*> rooms;
        map<string, Thing*> things;

        //Dynamic
        Container *inventory;
        Room *currentRoom;
        bool isLoaded;

        //Functions
        Thing *GetItem(string itemName);
        Thing *GetItemInRoom(string itemName);
};

#endif // GAME_H
