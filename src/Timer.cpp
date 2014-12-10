#include "Timer.h"
using namespace std;

Timer::Timer(bool running){
    running = false;
    reset = false;
    started = clock();
    stopped = started;
    duration = stopped - started;
    pauseDuration = duration;
}

bool Timer::isStarted(){
    if (running == true)
        return true;
    else
        return false;
}

void Timer::startTime(){
    if (!running)
        started = clock();
}

void Timer::stopTime(){
    if (running)
        stopped = clock();
}

clock_t Timer::doTimer(){
    if(!running){
        duration = stopped - started;
        return duration + pauseDuration;
    }
}

void Timer::resetTimer(){
    started = clock();
    stopped = started;
    duration = stopped - started;
}

clock_t Timer::pause(){
    if(running)
        stopTime();
        pauseDuration = stopped - started;
        return pauseDuration;
}

clock_t Timer::unPause(){
    if(!running){
        startTime();
    }
}
