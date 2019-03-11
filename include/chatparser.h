#ifndef CHATPARSER_H
#define CHATPARSER_H

#ifdef _WIN32
    /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501  /* Windows XP. */
    #endif
    /* winsock2.h must be included first */
    #include <winsock2.h>

    #include <windows.h>
    #include <Ws2tcpip.h>
#else
    /* Use POSIX-style sockets for non-Windows environments. */
    #include <arpa/inet.h>
    #include <cstring>
    #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
    #include <sys/socket.h>
    #include <unistd.h> /* Needed for close() */

    /* Redefine Windows types for Linux */
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR SO_ERROR
    #define LPSOCKADDR struct sockaddr *
#endif

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>

#include "room.h"
#include "thing.h"
#include "game.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "126"

using namespace std;

class ChatParser
{
    public:
        static void Init(Game* game);
        static int StartServer();

        /* Client */
        static string ChatError();
        static void ClientThread(SOCKET cSock, char* ip);
        static void LogOff(Player* p);
        static string NoText();
        static Player* ReceivePlayerFromLogin(SOCKET cSock);
        static string ReceiveResponse(SOCKET cSock);
        static string ReceiveResponse(SOCKET cSock, string prompt);
        static void SendStringToClient(SOCKET cSock, string message);

        /* Socket */
        static int SocketInit();
        static int SocketGetLastError();
        static int SocketShutdown(SOCKET sock);
        static int SocketClose(SOCKET sock);
        static int SocketQuit();

        /* Parsing */
        static string Parse(string parseMe, Player* p);
        static string ProcessCommand(string data, Player* p);

        /* Player commands */
        static bool Attack(Player* p, string attackMe, string attackWithMe);
        static bool Break(string breakMe, string withMe);
        static string Close(Player* p, Thing* closeMe);
        static bool Destroy(string destroyMe);
        static string Diagnose();
        static string Drink(Player* p, Thing* drinkMe);
        static string Drop(Player* p, Thing* dropMe);
        static void DropAll(Player* p);
        static string Eat(Player* p, Thing* eatMe);
        static string Examine(Player* p, Thing* examineMe);
        static void ExamineAll(Player* p);
        static string In(Player* p, Thing* inMe);
        static string Inventory(Player* p);
        static string Jump();
        static string Look(Player* p);
        static string Move(Player* p, string dir);
        static string MoveObj(Player* p, Thing* moveMe);
        static string Open(Player* p, Thing* openMe);
        static string Pray();
        static bool Put(Player* p, string putMe, string fillMe);
        static string Read(Player* p, Thing* readMe);
        static bool Restore(string state);
        static bool Save(string state);
        static string Shout();
        static bool Swap(string swapMe, string withMe);
        static string Take(Player* p, Thing* takeMe);
        static void TakeAll(Player* p);
        static bool Throw(Player* p, string throwMe, string hitMe);
        static bool Tie(string tieMe, string toMe);
        static bool Turn(Player* p, string turnMe);
        static string Turn(Player* p, Thing* turnMe, bool on);
        static bool Use(Player* p, string useMe);
        static bool Use(Player* p, string useMe, string onMe);

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
        static Game* game;
    private:
        static string DetermineCommand(vector<string>* arguments);
        static vector<Thing*> DeterminePossibleThings(Player* p, vector<string>* arguments);
        static bool InventoryHasThing(Player* p, Thing* thing);
        static bool RoomHasThing(Player* p, Thing* thing);

        static mutex cMutex;
        static string port;
        static vector<thread> threadList;
};

#endif // CHATPARSER_H
