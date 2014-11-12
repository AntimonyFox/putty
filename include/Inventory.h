#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <map>
#include "Thing.h"

using namespace::std;

struct hashValue
{
    int itemQuantity;
    Thing* item;
};

typedef map<string, hashValue> InventoryTable;
//map <string key, hashValue h> inventory;
class Inventory
{
public:
    Inventory();
    void add(string itemName, int itemQuantity);
    void remove(string itemName, int itemQuantity);
    void printInventory();
    void useItem(string itemName);
    Thing *getItem(string itemName);
private:
    InventoryTable *inventory;
};
#endif // INVENTORY_H
