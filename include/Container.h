#ifndef CONTAINER_H
#define CONTAINER_H

#include "Thing.h"

#include <iostream>
#include <string>
#include <map>

using namespace::std;

struct hashValue
{
    Thing *item;
    int itemQuantity;
};

typedef map<string, hashValue> ContainerTable;

class Container
{
    public:
        Container();
        void add(Thing *item);
        void remove(string itemName, int itemQuantity);
        void useItem(string itemName);
        Thing* GetItem(string itemName);
        int GetQuantity(string itemName);
        bool IsEmpty();
        void printContainer();
        ContainerTable *container;
};
#endif // CONTAINER_H
