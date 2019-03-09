#ifndef CHATPARSER_H
#define CHATPARSER_H

#include "room.h"
#include "thing.h"
#include "game.h"

#ifdef _WIN32
    /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501  /* Windows XP. */
    #endif
    #include <winsock2.h>
    #include <Ws2tcpip.h>
    #include <windows.h>
#else
    /* Use POSIX-style sockets for non-Windows environments. */
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
    #include <unistd.h> /* Needed for close() */

    #include <cstring>

    /* Redefine Windows types for Linux */
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR SO_ERROR
    #define LPSOCKADDR struct sockaddr *
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <thread>
#include <mutex>

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "126"


using namespace std;

class ChatParser
{
    public:
        static string Parse(string parseMe, Player* p);
        static Game *game;
        static string ProcessCommand(string data, Player* p);
        static void SendStringToClient(SOCKET cSock, string message);
        static string ReceiveResponse(SOCKET cSock);
        static string ReceiveResponse(SOCKET cSock, string prompt);
        static Player* ReceivePlayerFromLogin(SOCKET cSock);
        static void ClientThread(SOCKET cSock, char* ip);
        static int StartServer();
        static int SocketInit();
        static int SocketGetLastError();
        static int SocketShutdown(SOCKET sock);
        static int SocketClose(SOCKET sock);
        static int SocketQuit();
        static void LogOff(Player *p);

        static void Init(Game *game);
        static string ChatError();
        static string NoText();

        static string Look(Player* p);
        static string Inventory(Player* p);
        static void TakeAll(Player* p);
        static void DropAll(Player* p);
        static void ExamineAll(Player* p);

        //Steve
        static bool Throw(Player* p, string throwMe, string hitMe); //done
        static string Move(Player* p, string dir);
        static bool Use(Player* p, string useMe);
        static bool Use(Player* p, string useMe, string onMe);
        static string Drop(Player* p, Thing *dropMe); // done
        static string Take(Player* p, Thing *takeMe); // done
        static string Open(Player* p, Thing *openMe); //done
        static string Read(Player* p, Thing *readMe); //wip
        static bool Put(Player* p, string putMe, string fillMe);

        //Victor
        static string Drink(Player* p, Thing *drinkMe); //done
        static bool Turn(Player* p, string turnMe); //done
        static string Turn(Player* p, Thing *turnMe, bool on); //done
        static string MoveObj(Player* p, Thing *moveMe); //done
        static bool Attack(Player* p, string attackMe, string attackWithMe); //done
        static string Examine(Player* p, Thing *examineMe); //done
        static string Eat(Player* p, Thing *eatMe); //done
        static string Close(Player* p, Thing *closeMe); //done
        static bool Tie(string tieMe, string toMe); //done
        static bool Break(string breakMe, string withMe); //done
        static string In(Player *p, Thing *inMe);

        //Fox
        static string Jump(); //done
        static string Pray(); //done
        static string Diagnose(); //done
        static string Shout(); //done
        static bool Destroy(string destroyMe); //wip
        static bool Swap(string swapMe, string withMe);//wip
        static bool Save(string state); //wip
        static bool Restore(string state); //wip

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
        static string inAlias[3];

        static map<string, string> aliasMap;
    private:
        static mutex cMutex;
        static vector<thread> threadList;

        static string DetermineCommand(vector<string> * arguments);
        static vector<Thing*> DeterminePossibleThings(Player* p, vector<string> * arguments);
        static bool RoomHasThing(Player* p, Thing *thing);
        static bool InventoryHasThing(Player* p, Thing *thing);

        static string port;
};

#endif // CHATPARSER_H
