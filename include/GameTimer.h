#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "Game.h"

class GameTimer
{
    private:
        Game* game;

    public:
        GameTimer(Game* game);
        virtual ~GameTimer();
};

class AttackTimer :: public GameTimer{
    private:

    public:
        void timerFunction(){
            game->canAttack = true;
        }
};
#endif // GAMETIMER_H
