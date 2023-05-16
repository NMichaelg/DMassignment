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
    // cout<<LogicInfix2Postfix("a&b")<<endl;
    // cout<<LogicInfix2Postfix("a&b|a")<<endl;
    // cout<<LogicInfix2Postfix("p&q")<<endl;
    // cout<<LogicInfix2Postfix("~p")<<endl;
    // cout<<LogicInfix2Postfix("p|q")<<endl;
    // cout<<LogicInfix2Postfix("r|(p&q)")<<endl;
    // cout<<LogicInfix2Postfix("~(p&q)")<<endl;
    // cout<<LogicInfix2Postfix("(p&~q)|r")<<endl;
    // cout<<LogicInfix2Postfix("(p|~q)&r")<<endl;
    // cout<<LogicInfix2Postfix("~t->t&~w|(z&(p&(w&(p|p&q)|y&z&z)<->x&(~p|z)&~y))")<<endl;

    cout<<LogicInfix2Prefix("a&b")<<endl;
    cout<<LogicInfix2Prefix("a&b|a")<<endl;
    cout<<LogicInfix2Prefix("p&q")<<endl;
    cout<<LogicInfix2Prefix("~p")<<endl;
    cout<<LogicInfix2Prefix("p|q")<<endl;
    cout<<LogicInfix2Prefix("r|(p&q)")<<endl;
    cout<<LogicInfix2Prefix("~(p&q)")<<endl;
    cout<<LogicInfix2Prefix("(p&~q)|r")<<endl;
    cout<<LogicInfix2Prefix("(p|~q)&r")<<endl;
    cout<<LogicInfix2Prefix("~t->t&~w|(z&(p&(w&(p|p&q)|y&z&z)<->x&(~p|z)&~y))")<<endl;

    cout<<LogicPostfixPrefixCalculator("ab&","a b 1 0")<<endl; //FALSE
    cout<<LogicPostfixPrefixCalculator("&ab","a b 1 0")<<endl; //FASLE
    cout<<LogicPostfixPrefixCalculator("ab&a|","a b 1 0")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("|&aba","a b 1 0")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("pq&","p q 0 1")<<endl; //FALSE
    cout<<LogicPostfixPrefixCalculator("&pq","p q 0 1")<<endl; //FALSE
    cout<<LogicPostfixPrefixCalculator("p~","p 1")<<endl; //FALSE
    cout<<LogicPostfixPrefixCalculator("~p","p 1")<<endl; //FALSE
    cout<<LogicPostfixPrefixCalculator("pq|","p q 1 0")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("|pq","p q 1 0")<<endl; //TRUE 
    cout<<LogicPostfixPrefixCalculator("rpq&|","p q r 1 0 1")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("|r&pq","p q r 1 0 1")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("pq&~","p q 1 1")<<endl; //FALSE
    cout<<LogicPostfixPrefixCalculator("~&pq","p q 1 1")<<endl; //FALSE
    cout<<LogicPostfixPrefixCalculator("pq~&r|","p q r 1 0 0")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("|&p~qr","p q r 1 0 0")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("pq~|r&","p q r 0 0 1")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("&|p~qr","p q r 0 0 1")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("t~tw~&zpwpp|q&&y|z&z&&xp~z|&y~&<->&|->","t w z p q y x 1 1 1 1 1 1 1")<<endl; //TRUE
    cout<<LogicPostfixPrefixCalculator("->~t|&t~w&z<->&p&&|&w&|ppqyzz&&x|~pz~y","t w z p q y x 1 1 1 1 1 1 1")<<endl; //TRUE

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