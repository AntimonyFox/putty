#include <iostream>
#include "ChatParser.h"

using namespace std;

int main()
{
    string uInput;

    ChatParser::Init();

    while(true)
    {
        cout << "> ";
        getline(cin, uInput);
        ChatParser::Parse(uInput);
    }

    return 0;
}
