#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Thing.h"
#include "Container.h"
#include "Timer.h"
#include "Updatable.h"

#include <map>

class Game : public Updatable
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
        vector<Timer> timers;

        //Dynamic
        Container *inventory;
        shared_ptr<Room> currentRoom;
        bool isLoaded;
<<<<<<< HEAD
        bool canAttack = true;
=======
        bool hasError;
>>>>>>> Keywords added, ChatParser strings

        //Functions
        Thing *GetItem(string itemName);
        Thing *GetItemInRoom(string itemName);

        void lostGame();
};

#endif // GAME_H
