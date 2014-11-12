#include <iostream>
#include "PuttyParser.h"
#include "ChatParser.h"
#include "Inventory.h"
#include "Game.h"

using namespace std;

int main()
{
    Game game("game\\zork");
    game.Start();

//    Inventory inventory;                        // create inventory
//    auto inventoryTable = inventory.createInventory();
//
//    inventory.add(inventoryTable, "book", 5);
//    inventory.add(inventoryTable, "book", 3);
//    inventory.add(inventoryTable, "book", 2);                 // add to inventory
//    inventory.remove(inventoryTable, "book", 3);
//    inventory.remove(inventoryTable, "book", 3);                // remove from inventory
//    inventory.useItem(inventoryTable, "book");                  // use inventory
//    inventory.printInventory(inventoryTable);                 // print inventory

    return 0;
}
