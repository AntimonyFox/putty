#include <iostream>
#include "PuttyParser.h"
#include "ChatParser.h"
#include "Container.h"
#include "Game.h"

using namespace std;

int main()
{
    Game game("game/zork");
    game.Start();

    return 0;
}
