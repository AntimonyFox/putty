#include "inventory.h"

using namespace::std;

Inventory::Inventory() {
    inventory = new InventoryTable();
}

void Inventory::add(string itemName, int itemQuantity){
    bool add = true;

    if(inventory->count(itemName)) {
        hashValue temp = (*inventory)[itemName];
        temp.itemQuantity += itemQuantity;
        (*inventory)[itemName] =  temp;
        cout << itemName << " " << (*inventory)[itemName].itemQuantity << endl;
        add = false;
    }

    if (add == true)
        (*inventory)[itemName] = hashValue {itemQuantity};
}

void Inventory::remove(string itemName, int itemQuantity){
    bool remove = true;
    if (inventory->count(itemName)) {
        hashValue temp = (*inventory)[itemName];
        temp.itemQuantity -= itemQuantity;
        (*inventory)[itemName] =  temp;
        cout << itemName << " " << (*inventory)[itemName].itemQuantity << endl;
        remove = false;
    }

    if (remove == true)
        inventory->erase(itemName);
}

void Inventory::printInventory(){
    for ( auto key : *inventory)
        cout << key.first << " " << key.second.itemQuantity << endl;
}

void Inventory::useItem(string itemName){
    remove(itemName, 1);
}

Thing *Inventory::getItem(string itemName){
    hashValue temp = (*inventory)[itemName];
    return temp.item;
}
