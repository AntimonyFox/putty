#include "Inventory.h"
using namespace::std;

void Inventory::add(InventoryTable *inventory, string itemName, int itemQuantity){
    bool add = true;
    for ( auto key : *inventory)
        if (key.first == itemName) {
            key.second.itemQuantity += itemQuantity;
            add = false;
        }

    if (add == true)
        (*inventory)[itemName] = hashValue {itemQuantity};
}

void Inventory::remove(InventoryTable *inventory, string itemName, int itemQuantity){
    bool remove = true;
    for ( auto key : *inventory)
        if (key.first == itemName) {
            key.second.itemQuantity -= itemQuantity;
            remove = false;
        }

    if (remove == true)
    inventory->erase(itemName);
}

void Inventory::printInventory(InventoryTable *inventory){
    for ( auto key : *inventory)
        cout << key.first << key.second.itemQuantity << endl;
}

void Inventory::useItem(InventoryTable *inventory, string itemName){
    remove(inventory, itemName, 1);
}

InventoryTable *Inventory::createInventory()
{
    InventoryTable *inventoryTable = new InventoryTable();
    return inventoryTable;
}
