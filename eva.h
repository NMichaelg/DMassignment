#ifndef EVA_H
#define EVA_H

#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include <math.h>
#include <sstream>
#include <iostream>
using namespace std;

string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
string LogicInfix2Postfix(string infix);

vector<string> split_logic(string expression);
vector<string> splitExpression(string expression);
string PostfixPrefixCalculator(string input);
int isOperator(char ch);
int precedence(string ch);
int logic_precedence(string ch);
#endif
