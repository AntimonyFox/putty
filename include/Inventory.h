#ifndef INVENTORY_H
#define INVENTORY_H

include <unordered_map>
using namespace::std;

struct hashValue{
    int itemQuantity;
    string itemQuantiy;
};

template <string key, hashValue> hashTable;


class Inventory
{
    public:
        Inventory();
        virtual ~Inventory();
    protected:
    private:
        void add()
};

#endif // INVENTORY_H
