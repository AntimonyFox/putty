#include "container.h"

using namespace::std;

Container::Container() {
    container = new ContainerTable();
}

void Container::add(Thing* item){
    bool add = true;

    string itemName = item->filename;
    if(container->count(itemName)) {
        hashValue temp = (*container)[itemName];
        temp.itemQuantity += 1;
        (*container)[itemName] = temp;
        add = false;
    }

    if (add == true)
        (*container)[itemName] = hashValue {item, 1};
}

void Container::remove(string itemName, int itemQuantity){
    bool remove = true;
    if (container->count(itemName)) {
        hashValue temp = (*container)[itemName];
        temp.itemQuantity -= itemQuantity;
        (*container)[itemName] =  temp;
        if (temp.itemQuantity > 0)
            remove = false;
    }

    if (remove == true)
        container->erase(itemName);
}

void Container::useItem(string itemName){
    remove(itemName, 1);
}

Thing* Container::GetItem(string itemName)
{
    Thing *thing = nullptr;
    if (container->count(itemName))
    {
        thing = (*container)[itemName].item;
    }
    else
    {
        //For each room or inventory thing (depth=0)
        for (auto cPair : *container)
        {
            Thing *topThing = cPair.second.item;
            if (topThing->isContainer && topThing->isOpen)
            {
                for (auto innerPair : topThing->contents)
                {
                    Thing *innerThing = innerPair.second;
                    if (innerThing->contents.count(itemName))
                    {
                        thing = innerThing->contents[itemName];
                        innerThing->contents.erase(itemName);
                        break;
                    }
                }
            }
        }
    }

    //Thing isn't visible or doesn't exist
    return thing;
}

int Container::GetQuantity(string itemName)
{
//    Thing *thing = GetItem(itemName);
//    if (thing != nullptr)
//        return thing.itemQuantity;
    return 1;
}

bool Container::IsEmpty()
{
    return container->empty();
}

string Container::printContainer()
{
    string output = "";
    for (auto key : *container) {
        stringstream iss;
        iss << key.second.itemQuantity;
        output += key.first + " " + iss.str() + "\n";
    }
    return output;
}
