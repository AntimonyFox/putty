#ifndef CHATPARSER_H
#define CHATPARSER_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>

using namespace std;

class tempObj{};
class tempRoom{};


class ChatParser
{
    public:
        vector<string> static Parse(string parseMe);

        static void Init();

        static void Look();
        static void Inventory();
        static void TakeAll();
        static void DropAll();
        static void ExamineAll();

        static bool Throw(tempObj * throwMe, tempObj * hitMe);
        static bool Move(string dir);
        static bool Use(tempObj * useMe);
        static bool Use(tempObj * useMe, tempObj * onMe);
        static bool Drop(tempObj * dropMe);
        static bool Take(tempObj * takeMe);
        static bool Open(tempObj * openMe);
        static bool Read(tempObj * readMe);
        static bool Put(tempObj * putMe, tempObj * fillMe);
        static bool Drink(tempObj * drinkMe);
        static bool Turn(tempObj * turnMe, bool on);
        static bool MoveObj(tempObj * moveMe);
        static bool Attack(tempObj * attackMe, tempObj * attackWithMe);
        static bool Examine(tempObj * examineMe);
        static bool Eat(tempObj * eatMe);
        static bool Close(tempObj * closeMe);
        static bool Tie(tempObj * tieMe, tempObj * toMe);
        static bool Break(tempObj * breakMe, tempObj * withMe);
        static bool Jump();
        static bool Pray();
        static bool Diagnose();
        static bool Shout();
        static bool Destroy(tempObj * destroyMe);
        static bool Swap(tempObj * swapMe, tempObj * withMe);
        static bool LookAt(tempObj * lookAtMe);
        static bool Save(int state);
        static bool Restore(int state);
        weak_ptr<int> currentRoom;

        static string lookAlias[3];
        static string inventoryAlias[3];

        static string moveAlias[3];
        static string northAlias[2];
        static string eastAlias[2];
        static string southAlias[2];
        static string westAlias[2];
        static string northEastAlias[2];
        static string northWestAlias[2];
        static string southEastAlias[2];
        static string southWestAlias[2];
        static string upAlias[1];
        static string downAlias[1];
        static string throwAlias[2];
        static string useAlias[2];
        static string dropAlias[3];
        static string takeAlias[4];
        static string openAlias[2];
        static string readAlias[1];
        static string putAlias[3];
        static string drinkAlias[2];
        static string turnAlias[2];
        static string moveObjAlias[2];
        static string attackAlias[4];
        static string examineAlias[2];
        static string eatAlias[2];
        static string closeAlias[2];
        static string tieAlias[4];
        static string breakAlias[2];
        static string jumpAlias[2];
        static string prayAlias[1];
        static string shoutAlias[3];
        static string diagnoseAlias[2];
        static string saveAlias[1];
        static string restoreAlias[2];

        static map<string, string> aliasMap;

};

#endif // CHATPARSER_H
