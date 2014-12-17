#include "ThingsTimer.h"

ThingsTimer::ThingsTimer(Thing *thing) : Timer()
{
    this->thing = thing;
}

ThingsTimer::~ThingsTimer()
{
    //dtor
}
