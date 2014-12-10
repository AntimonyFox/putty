#ifndef TIMER_H
#define TIMER_H
#include <ctime>

class Timer
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
};
#endif // TIMER_H
