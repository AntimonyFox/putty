#include <iostream>
#include "PuttyParser.h"
#include "ChatParser.h"

using namespace std;

int main()
{
    PuttyParser().parse("C:\\users\\fox\\desktop\\zork");
    cout << "Hello world!" << endl;

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
