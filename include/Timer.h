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
        Timer();
        bool isStarted();
        void startTime();
        void stopTime();

        clock_t pause();
        void unPause();

        void resetTimer();

        virtual void timerFunction();
        virtual void update();

        void setDuration(clock_t setDuration);
};
#endif // TIMER_H
