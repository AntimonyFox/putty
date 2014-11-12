#include <iostream>
#include "PuttyParser.h"
#include "ChatParser.h"
#include "Inventory.h"

using namespace std;

int main()
{
    PuttyParser().parse("game\\zork");
    cout << "Hello world!" << endl;

    string uInput;

    ChatParser::Init();

    while(true)
    {
        cout << "> ";
        getline(cin, uInput);
        ChatParser::Parse(uInput);
    }
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
