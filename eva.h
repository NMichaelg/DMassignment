#ifndef EVA_H
#define EVA_H

#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;
string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
vector<string> splitExpression(string expression);
string PostfixPrefixCalculator(string input);
int isOperator(char ch);
#endif
