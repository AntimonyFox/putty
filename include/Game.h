#ifndef GAME_H
#define GAME_H

#include <map>
#include <memory>
#include <mutex>

#include "Container.h"
#include "Player.h"
#include "Room.h"
#include "Thing.h"
#include "Timer.h"
#include "Updatable.h"

using std::string;

class Game : public Updatable
{
    friend class PuttyParser;
    friend class ChatParser;

    public:
        Game(string path);
        virtual ~Game();
        void Start();
        virtual void update();

    private:
        //Static
        string startingRoom;
        map<string, shared_ptr<Room>> rooms;
        map<string, Thing*> things;
        vector<Timer> timers;
        mutex ipMutex;

        //Dynamic
        Container* inventory;
        shared_ptr<Room> currentRoom;
        bool isLoaded;
        bool hasError;
        map<string, Player*> playerMap;

        //Functions
        Thing* GetItem(string itemName);
        Thing* GetItemInRoom(string itemName);

        void LostGame();
        Player* CreatePlayer(string username);
        Player* GetPlayer(string username);
        bool DestroyPlayer(string username);
};

#endif // GAME_H
