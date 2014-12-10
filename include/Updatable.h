#ifndef UPDATABLE_H
#define UPDATABLE_H


class Updatable
{
    private:
        bool updatable;
        bool needUpdate;
    public:
        Updatable();
        ~Updatable();
        virtual void update() = 0;

};

#endif // UPDATABLE_H
