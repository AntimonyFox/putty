#include "timer.h"
using namespace std;

Timer::Timer()
{
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
    if (!running){
        started = clock();
        running = true;
    }
}

void Timer::stopTime(){
    if (running)
        stopped = clock();
}

void Timer::timerFunction()
{

}


void Timer::update(){
    if ((clock() - started) > duration){
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
    // Verify this logic
    pauseDuration = stopped - started;
    return pauseDuration;
}

void Timer::unPause(){
    if(!running){
        startTime();
    }
}

void Timer::setDuration(clock_t setDuration){
    duration = setDuration;
}
