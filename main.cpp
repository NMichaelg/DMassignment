#include <iostream>
#include "eva.h"
void logic_test();
void arth_test();
int main(){
    //arth_test();
    logic_test();
    return 0;
}
void logic_test(){
    cout<<LogicInfix2Postfix("~a")<<endl;
    cout<<LogicInfix2Postfix("a&b")<<endl;
    cout<<LogicInfix2Postfix("a&b|a")<<endl;
    cout<<LogicInfix2Postfix("p&q")<<endl;
    cout<<LogicInfix2Postfix("~p")<<endl;
    cout<<LogicInfix2Postfix("p|q")<<endl;

    cout<<LogicInfix2Postfix("p->q")<<endl;
    cout<<LogicInfix2Postfix("p<->q")<<endl;


    cout<<LogicInfix2Postfix("r|(p&q)")<<endl;
    cout<<LogicInfix2Postfix("~(p&q)")<<endl;
    cout<<LogicInfix2Postfix("(p&~q)|r")<<endl;
    cout<<LogicInfix2Postfix("(p|~q)&r")<<endl;
    cout<<LogicInfix2Postfix("~t->t&~w|(z&(p&(w&(p|p&q)|y&z&z)<->x&(~p|z)&~y))")<<endl;
}
void arth_test(){
    //cout<<Infix2Postfix("(3+4)*(5-2)/(6+1)")<<endl;
    //cout<<Infix2Prefix("49*(41*39)-(145+78)+193+(121*135+101-88)")<<endl;
    cout<<PostfixPrefixCalculator("1 2 +")<<endl;
    cout<<PostfixPrefixCalculator("+ 1 2")<<endl;
    cout<<PostfixPrefixCalculator("13 15 -")<<endl;
    cout<<PostfixPrefixCalculator("- 13 15")<<endl;
    cout<<PostfixPrefixCalculator("5 6 *")<<endl;
    cout<<PostfixPrefixCalculator("* 5 6")<<endl;
    cout<<PostfixPrefixCalculator("10 15 /")<<endl;
    cout<<PostfixPrefixCalculator("/ 10 15")<<endl;
    cout<<PostfixPrefixCalculator("8 4 / 9 3 - +")<<endl;
    cout<<PostfixPrefixCalculator("+ / 8 4 - 9 3")<<endl;

    // cout<<PostfixPrefixCalculator("20 2 ^")<<endl;
    // cout<<PostfixPrefixCalculator("^ 20 2")<<endl;

    cout<<PostfixPrefixCalculator("3 4 + 5 2 - * 6 1 + /")<<endl;
    cout<<PostfixPrefixCalculator("/ * + 3 4 - 5 2 + 6 1")<<endl;
    cout<<PostfixPrefixCalculator("49 41 39 * * 145 78 + - 193 + 121 135 * 101 + 88 - +")<<endl;
    cout<<PostfixPrefixCalculator("+ + - * 49 * 41 39 + 145 78 193 - + * 121 135 101 88")<<endl;
    cout<<PostfixPrefixCalculator("59 107 83 * 72 * 91 * 27 112 153 * 111 76 + * - / +")<<endl;
    cout<<PostfixPrefixCalculator("+ 59 / * * * 107 83 72 91 - 27 * * 112 153 + 111 76")<<endl;
    cout<<PostfixPrefixCalculator("133 179 + 60 / 157 133 * 177 19 10 2 4 * - ^ * + *")<<endl;
    cout<<PostfixPrefixCalculator("* / + 133 179 60 + * 157 133 * 177 ^ 19 - 10 * 2 4")<<endl;
    cout<<PostfixPrefixCalculator("987 654 321 123 / * + 2 ^ 456 789 + -")<<endl;
    cout<<PostfixPrefixCalculator("- ^ + 987 * 654 / 321 123 2 + 456 789")<<endl;

}