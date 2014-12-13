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
        static string Parse(string parseMe);
        static Game *game;

        static void Init(Game *game);
        static string ChatError();
        static string NoText();

        static string Look();
        static string Inventory();
        static void TakeAll();
        static void DropAll();
        static void ExamineAll();

        //Steve
        static bool Throw(string throwMe, string hitMe); //done
        static string Move(string dir);
        static bool Use(string useMe);
        static bool Use(string useMe, string onMe);
        static string Drop(Thing *dropMe); // done
        static string Take(Thing *takeMe); // done
        static string Open(Thing *openMe); //done
        static string Read(Thing *readMe); //wip
        static bool Put(string putMe, string fillMe);

        //Victor
        static string Drink(Thing *drinkMe); //done
        static bool Turn(string turnMe); //done
        static string Turn(Thing *turnMe, bool on); //done
        static string MoveObj(Thing *moveMe); //done
        static bool Attack(string attackMe, string attackWithMe); //done
        static string Examine(Thing *examineMe); //done
        static string Eat(Thing *eatMe); //done
        static string Close(Thing *closeMe); //done
        static bool Tie(string tieMe, string toMe); //done
        static bool Break(string breakMe, string withMe); //done

        //Fox
        static string Jump(); //done
        static string Pray(); //done
        static string Diagnose(); //done
        static string Shout(); //done
        static bool Destroy(string destroyMe); //wip
        static bool Swap(string swapMe, string withMe);//wip
        static bool Save(string state); //wip
        static bool Restore(string state); //wip
        weak_ptr<int> currentRoom; //done

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
    private:
        static string DetermineCommand(vector<string> * arguments);
        static vector<Thing*> DeterminePossibleThings(vector<string> * arguments);
        static bool RoomHasThing(Thing *thing);
        static bool InventoryHasThing(Thing *thing);
};

#endif // CHATPARSER_H
