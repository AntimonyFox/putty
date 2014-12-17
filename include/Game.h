#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Player.h"
#include "Thing.h"
#include "Container.h"
#include "Timer.h"
#include "Updatable.h"

#include <memory>
#include <mutex>
#include <map>

using namespace std;

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
        mutex ipMutex;

        //Dynamic
        Container *inventory;
        shared_ptr<Room> currentRoom;
        bool isLoaded;
        bool canAttack = true;
        bool hasError;
        map<string, Player*> ipMap;

        //Functions
        Thing *GetItem(string itemName);
        Thing *GetItemInRoom(string itemName);

        void lostGame();
        Player* CreatePlayer(string ip);
        Player* GetPlayer(string ip);
};

#endif // GAME_H
