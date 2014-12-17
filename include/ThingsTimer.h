#ifndef THINGSTIMER_H
#define THINGSTIMER_H

#include "Timer.h"
#include "Thing.h"
#include <iostream>

class ThingsTimer : public Timer
{
    public:
        ThingsTimer(Thing *thing);
        virtual ~ThingsTimer();
    protected:
        Thing* thing;
};

class BombTimer : public ThingsTimer
{
    private:

    public:
        void timerFunction(){
//            game->lostGame();
//            cout << "you lost the game" << endl;
        }
};

class DoorTimer : public ThingsTimer
{
    private:

    public:
        void timerFunction(){
            thing->isOpen = false;
            cout << "Door has closed" << endl;
        }
};
#endif // THINGSTIMER_H
