#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "Game.h"

class GameTimer
{
    public:
        GameTimer(Game* game);
        virtual ~GameTimer();

    protected:
        Game* game;
};

class AttackTimer : public GameTimer
{
    public:
        void timerFunction() {
//            game->canAttack = true;
        }
};
#endif // GAMETIMER_H
