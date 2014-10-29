#include <iostream>
#include "Inventory.h"

using namespace std;

int main()
{
    Inventory inventory;                        // create inventory
    auto inventoryTable = inventory.createInventory();

    inventory.add(inventoryTable, "book", 5);                   // add to inventory
    inventory.remove(inventoryTable, "book", 3);                // remove from inventory
    inventory.useItem(inventoryTable, "book");                  // use inventory
    //inventory.printInventory(inventoryTable);                 // print inventory

    return 0;
}
