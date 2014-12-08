#ifndef TIMER_H
#define TIMER_H


class Timer
{
    private:
        float startTime;
        float endTime;
        float time;
        float currentTime;

    public:
        Timer();
        virtual ~Timer();
        void setTime(float time);
        float getTime();
        float startTime();
        float endTime();
};

#endif // TIMER_H
