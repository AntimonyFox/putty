#ifndef THINGSTIMER_H
#define THINGSTIMER_H

#include "Timer.h"
#include <iostream>
#include <stdio>

class ThingsTimer : public Timer
{
    private:
        Thing* thing;
    public:
        ThingsTimer(Thing *thing);
        virtual ~ThingsTimer();
};

class BombTimer : public ThingsTimer
{
    private:

    public:
        void timerFunction(){
            game->lostGame();
            cout << "you lost the game" << endl;
        }
};

class DoorTimer : public ThingsTimer
{
    private:

    public:
        void timerFunction(){
            isOpen = false;
            cout << "Door has closed" << endl;
        }
};
#endif // THINGSTIMER_H
