#include <iostream>
#include "eva.h"
int main(){
    cout<<"Hello World"<<endl;
    //cout<<Infix2Postfix("(3+4)*(5-2)/(6+1)")<<endl;
    cout<<Infix2Prefix("49*(41*39)-(145+78)+193+(121*135+101-88)")<<endl;
    return 0;
}