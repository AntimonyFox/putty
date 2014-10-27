#include <iostream>
#include "ChatParser.h"

using namespace std;

int main()
{
    string uInput;

    while(true)
    {
        cout << "> ";
        getline(cin, uInput);
        ChatParser::Parse(uInput);
    }

    return 0;
}
