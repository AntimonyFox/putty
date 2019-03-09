#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

using std::string;
using std::vector;

string ToLower(string lowerMe);
string RemoveSpaces(string changeMe);
string Capitalize(string capMe);
string Implode(vector<string> * arguments, string join);
bool IsNumber(string check);
void RemoveThe(vector<string> * purgeMe);
void RemoveFirst(vector<string> * purgeMe);
vector<string> * StringToArguments(string parseMe);

#endif // UTILITIES_H