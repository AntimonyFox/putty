#include "Inventory.h"
using namespace::std;

void Inventory::add(InventoryTable *inventory, string itemName, int itemQuantity){
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

void Inventory::remove(InventoryTable *inventory, string itemName, int itemQuantity){
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

void Inventory::printInventory(InventoryTable *inventory){
    for ( auto key : *inventory)
        cout << key.first << " " << key.second.itemQuantity << endl;
}

void Inventory::useItem(InventoryTable *inventory, string itemName){
    remove(inventory, itemName, 1);
}

InventoryTable *Inventory::createInventory(){
    InventoryTable *inventoryTable = new InventoryTable();
    return inventoryTable;
}
