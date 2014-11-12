#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Thing.h"
#include "Inventory.h"

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
        map<string, Room*> rooms;
        map<string, Thing*> things;
        string startingRoom;
        Room *currentRoom;
        Inventory *inventory;
};

#endif // GAME_H
