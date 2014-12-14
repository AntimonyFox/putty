#include "Timer.h"
using namespace std;

bool Timer::Timer(){
    Timer.running = false;
    Timer.reset = false;
    Timer.started = clock();
    Timer.stopped = Time.started;
    Timer.duration = Timer.stopped - Timer.started;
    Timer.pauseDuration = Timer.duration;
}

bool Timer::isStarted(){
    if (running == true)
        return true;
    else
        return false;
}

void Timer::startTime(){
    if (!running){
        started = clock();
        running = true;
    }
}

void Timer::stopTime(){
    if (running)
        stopped = clock();
}

clock_t Timer::update(){
    if ((clock() - startTime) > duration){
        timerFunction();
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

void Timer::setDuration(clock_t setDuration){
    duration = setDuration;
}
