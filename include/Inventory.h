#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <iostream>
#include <map>
using namespace::std;

struct hashValue
{
    int itemQuantity;
    //object toBeEntity;
};

typedef map<string, hashValue> InventoryTable;
//map <string key, hashValue h> inventory;
class Inventory
{
private:
    string itemName;
public:
    void add(InventoryTable *inventory, string itemName, int itemQuantity);
    void remove(InventoryTable *inventory, string itemName, int itemQuantity);
    void printInventory(InventoryTable *inventory);
    void useItem(InventoryTable *inventory, string itemName);
    InventoryTable* createInventory();

};
#endif // INVENTORY_H
