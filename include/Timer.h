#ifndef TIMER_H
#define TIMER_H
#include <ctime>
#include "Updatable.h"

class Timer : public Updatable
{
    private:
        clock_t stopped, started, duration, pauseDuration;
        bool running, reset;

    public:
        Timer(bool running);
        bool isStarted();
        void startTime();
        void stopTime();

        clock_t pause();
        clock_t unPause();

        clock_t doTimer();
        void resetTimer();

        virtual void timerFunction() = 0;
        virtual void update(clock_t duration);
};
#endif // TIMER_H
