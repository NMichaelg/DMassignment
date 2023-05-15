#ifndef EVA_H
#define EVA_H

#include <stack>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
vector<string> splitExpression(string expression);
#endif
