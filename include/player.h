#ifndef PLAYER_H
#define PLAYER_H

class Room;

#include "room.h"
#include "container.h"
#include <memory>

class Player
{
    public:
    shared_ptr<Room> currentRoom;
    Container *inventory;
    string name;

    bool inUse;
};

#endif // PLAYER_H
