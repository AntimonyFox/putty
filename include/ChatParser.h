#ifndef CHATPARSER_H
#define CHATPARSER_H

#include "Room.h"
#include "Thing.h"
#include "Game.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using namespace std;

class ChatParser
{
    public:
        vector<string> static Parse(string parseMe);
        static Game *game;

        static void Init(Game *game);
        static void ChatError();
        static void NoText();

        static void Look();
        static void Inventory();
        static void TakeAll();
        static void DropAll();
        static void ExamineAll();

        static bool Throw(string throwMe, string hitMe);
        static bool Move(string dir);
        static bool Use(string useMe);
        static bool Use(string useMe, string onMe);
        static bool Drop(string dropMe);
        static bool Take(string takeMe);
        static bool Open(string openMe);
        static bool Read(string readMe);
        static bool Put(string putMe, string fillMe);
        static bool Drink(string drinkMe);
        static bool Turn(string turnMe);
        static bool Turn(string turnMe, string on);
        static bool MoveObj(string moveMe);
        static bool Attack(string attackMe, string attackWithMe);
        static bool Examine(string examineMe);
        static bool Eat(string eatMe);
        static bool Close(string closeMe);
        static bool Tie(string tieMe, string toMe);
        static bool Break(string breakMe, string withMe);
        static bool Jump();
        static bool Pray();
        static bool Diagnose();
        static bool Shout();
        static bool Destroy(string destroyMe);
        static bool Swap(string swapMe, string withMe);
        static bool LookAt(string lookAtMe);
        static bool Save(string state);
        static bool Restore(string state);
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
