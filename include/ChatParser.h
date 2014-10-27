#ifndef CHATPARSER_H
#define CHATPARSER_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class tempObj{};
class tempRoom{};


class ChatParser
{
    public:
        vector<string> static Parse(string parseMe);
        void Look();
        void Inventory();
        void TakeAll();
        void DropAll();
        void ExamineAll();

        bool Throw(tempObj * throwMe, tempObj * hitMe);
        bool Move(string dir);
        bool Use(tempObj * useMe);
        bool Use(tempObj * useMe, tempObj * onMe);
        bool Drop(tempObj * dropMe);
        bool Take(tempObj * takeMe);
        bool Open(tempObj * openMe);
        bool Read(tempObj * readMe);
        bool Put(tempObj * putMe, tempObj * fillMe);
        bool Drink(tempObj * drinkMe);
        bool Turn(tempObj * turnMe, bool on);
        bool MoveObj(tempObj * moveMe);
        bool Attack(tempObj * attackMe, tempObj * attackWithMe);
        bool Examine(tempObj * examineMe);
        bool Eat(tempObj * eatMe);
        bool Close(tempObj * closeMe);
        bool Tie(tempObj * tieMe, tempObj * toMe);
        bool Break(tempObj * breakMe, tempObj * withMe);
        bool Jump();
        bool Pray();
        bool Diagnose();
        bool Shout();
        bool Destroy(tempObj * destroyMe);
        bool Swap(tempObj * swapMe, tempObj * withMe);
        bool LookAt(tempObj * lookAtMe);
        bool Save(int state);
        bool Restore(int state);
        weak_ptr<int> currentRoom;

    protected:
    private:
        static const string lookAlias[] = {"look", "l", "description"};
        static const string inventoryAlias[] = {};

        static const string moveAlias[] = {"go", "walk", "run"};
        static const string northAlias[] = {"north", "n"};
        static const string eastAlias[] = {"east", "e"};
        static const string soutAlias[] = {"south", "s"};
        static const string westAlias[] = {"west",};
        static const string northEastAlias[] = {"northeast", "ne"};
        static const string northWestAlias[] = {"northwest", "nw"};
        static const string southEastAlias[] = {"southeast", "se"};
        static const string southWestAlias[] = {"soutwest", "sw"};
        static const string upAlias[] = {"up"};
        static const string downAlias[] = {"down"};

        static const string throwAlias[] = {"throw", "toss"};
        static const string useAlias[] = {"use", "u"};
        static const string dropAlias[] = {"drop", "unhand", "d"};
        static const string takeAlias[] = {"take", "get", "grab", "t"};
        static const string openAlias[] = {"open", "o"};
        static const string readAlias[] = {"read"};
        static const string putAlias[] = {"put", "place", "set"};
        static const string drinkAlias[] = {"drink", "swallow"};
        static const string turnAlias[] = {"turn", "switch"};
        static const string moveObjAlias[] = {"move", "push"};
        static const string attackAlias[] = {"attack", "kill", "sick", "swing at"};
        static const string examineAlias[] = {"examine", "look at"};
        static const string eatAlias[] = {"eat", "consume"};
        static const string closeAlias[] = {"close", "c"};
        static const string tieAlias[] = {"tie", "fasten", "attach", "join"};
        static const string breakAlias[] = {"break", "destroy"};
        static const string jumpAlias[] = {"jump", "hop"};
        static const string prayAlias[] = {"pray"};
        static const string shoutAlias[] = {"shout", "yell", "bark"};
        static const string diagnoseAlias[] = {"diagnose", "health"};
        static const string saveAlias[] = {"save"};
        static const string restoreAlias[] = {"restore", "load"};

};

#endif // CHATPARSER_H
