#include "eva.h"
//SUPPORT FUNCTION
int isOperator(string ch)
{
    return (ch == "+" || ch == "-" || ch == "*" || ch == "/"
            || ch == "^");
}
int isLogicoperator(string ch){

    return (ch == "&" || ch == "|" || ch == "->" || ch == "~" || ch == "<->");
}

int precedence(string ch) {
    if (ch == "+" || ch == "-") {
    return 1;
    } else if (ch == "*" || ch == "/") {
    return 2;
    } else if (ch == "^") {
    return 3;
    } else {
    return 0;
    }
}
int logic_precedence(string ch){
    if (ch == "<->") {
        return 1;
    } else if (ch == "->") {
        return 2;
    } else if (ch == "|") {
        return 4;
    } else if (ch== "&") {
        return 4;
    } else if (ch=="~"){
        return 5;
    }    
    else {
        return 0;
    }
}
vector<string> split_logic(string expression) {
    vector<string> tokens;
    stringstream ss(expression);
    string token ;
    while (getline(ss, token, ' ')) {
        if(isalpha(token[0])){
            tokens.push_back(token.substr(0,1));
            token = token.substr(1);
        }
        std::size_t found = token.find_first_of("&|-><->()~");
        while (found != std::string::npos) {
            if (isalpha(token[0])){
                tokens.push_back(token.substr(0,1));
                token = token.substr(1);
                found = token.find_first_of("&|-><->()~");
            }
            if(token[found] == '&' || token[found] == '|' || token[found] == '-' || token[found] == '<' || token[found] == '(' || token[found] == ')'){
                if(token[found] == '-'){
                    tokens.push_back(token.substr(found,2));
                    tokens.push_back(token.substr(found+2, 1));
                    token = token.substr(found + 3);
                }else if (token[found] == '<'){
                    tokens.push_back(token.substr(found,3));
                    tokens.push_back(token.substr(found+3, 1));
                    token = token.substr(found + 4);
                }else if (token[found] == '(' || token[found] == ')'){
                    tokens.push_back(token.substr(found,1));
                    token = token.substr(found + 1);
                }
                else{
                    tokens.push_back(token.substr(found,1));
                    tokens.push_back(token.substr(found+1, 1));            
                    // foundarr[0] = token.find("&");
                    // foundarr[1] = token.find("|");
                    // foundarr[2] = token.find("->");
                    // foundarr[3] = token.find("<->");
                    token = token.substr(found + 2);
                }
            }else if (token[found] == '~'){
                tokens.push_back(token.substr(found,1));
                tokens.push_back(token.substr(found+1,1));
                token = token.substr(found + 2);
            }else{
                //TO DO EXCEPTION
            }
            found = token.find_first_of("&|~-><->()");
        }
    }

    return tokens;
}
vector<string> splitExpression(string expression) {
    vector<string> tokens;
    string currentToken = "";

    for (unsigned int i = 0; i < expression.length(); i++) {
        string c ;
        c += expression[i];

        // If the character is a digit or a decimal point, add it to the current token
        if (isalpha (c[0])){
            currentToken += c;
            tokens.push_back(currentToken);
            currentToken = "";
        }
        else if (isdigit(c[0])) {
            currentToken += c;
            for (i = i+1; i<expression.length();i++){
                if(!isdigit(expression[i])){
                    i = i-1;
                    break;
                }else{
                    currentToken += expression[i];
                }
            }
            // If the current token is the only token in the vector or the previous character was not a digit,
            // add the current token to the vector and reset the current token
            tokens.push_back(currentToken);
            currentToken = "";
        }
        // If the character is a symbol, add it to the vector as a separate token
        else if (c == "(" || c == ")" || isOperator(c)) {
            tokens.push_back(c);
        }else{
            
        }
    }

    // Add the last token to the vector if it exists
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

vector<string> splitfix(string input){
    vector<std::string> result;
    string temp = "";

    for (unsigned int i = 0; i < input.size(); i++) {
        if (input[i] == ' ') {
            result.push_back(temp);
            temp = "";
        }
        else {
            temp += input[i];
        }
    }

    if (temp.size() > 0) {
        result.push_back(temp);
    }

    return result;
}
vector<string> splitlogicfix(const string& input){
    vector<std::string> result;
    for (unsigned int i = 0; i < input.size(); i++) {
        if (isalpha(input[i])) {
            result.push_back(input.substr(i,1));
        }
        else {
            if(input[i] == '-'){
                result.push_back(input.substr(i,2));
                i++;
            }else if (input[i] == '<'){
                result.push_back(input.substr(i,3));
                i += 2;
            }else{
                result.push_back(input.substr(i,1));
            }
        }
    }
    return result;
}
//END OF SUPPORT FUNCTION


string Infix2Postfix(string infix) {
  stack<string> stk;

  // Create a string to store postfix expression
  string postfix = "";

  // Iterate over the infix expression
  for (unsigned int i = 0; i < infix.length(); i++) {
    string ch;
    ch += infix[i];

    // If ch is a number, append it to the postfix expression with a space
    if (isdigit(ch[0])) {
        for (i = i+1; i < infix.length();i++){
            if (!isdigit(infix[i])){
                i = i-1;
                break;
            }else{
                ch += infix[i];
            }
        }
        postfix += ch;
        postfix += ' ';
    }
    // If ch is an opening parenthesis, push it to the stack
    else if (ch == "(") {
      stk.push(ch);
    }
    // If ch is a closing parenthesis, pop all operators from the stack
    // and append them to the postfix expression until an opening parenthesis is popped
    else if (ch == ")") {
      while (!stk.empty() && stk.top() != "(") {
        postfix += stk.top();
        postfix += ' ';
        stk.pop();
      }
      stk.pop(); // Pop the '('
    }
    // If ch is an operator, pop all operators from the stack
    // that have higher or equal precedence than ch and append them to the postfix expression
    else {
      while (!stk.empty() && precedence(ch) <= precedence(stk.top())) {
        postfix += stk.top();
        postfix += ' ';
        stk.pop();
      }
        stk.push(ch);
    }
  }

  // While stack is not empty, pop and print operators
  while (!stk.empty()) {
    postfix += stk.top();
    postfix += ' ';
    stk.pop();
  }

  // Remove the trailing space
  postfix.pop_back();

  return postfix;
}

string Infix2Prefix(string infix) {
    vector<string> arrs = splitExpression(infix);
    reverse(arrs.begin(),arrs.end());
    for (unsigned int i =0 ; i< arrs.size();i++){
        if (arrs[i] == "(") {
            arrs[i] = ")";
        }
        else if (arrs[i] == ")") {
            arrs[i] = "(";
        }
    }
    arrs.push_back(")");
    arrs.insert(arrs.begin(),"(");
    int l = arrs.size();
    stack<string> char_stack;
    vector<string> output;
 
    for (int i = 0; i < l; i++) {
 
        // If the scanned character is an
        // operand, add it to output.
        if (isdigit(arrs[i][0])){
            output.push_back(arrs[i]);
            output.push_back(" ");
        }
        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (arrs[i] == "(")
            char_stack.push("(");
 
        // If the scanned character is an
        // ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (arrs[i] == ")") {
            while (char_stack.top() != "(") {
                output.push_back(char_stack.top());
                output.push_back(" ");
                char_stack.pop();
            }
 
            // Remove '(' from the stack
            char_stack.pop();
        }
 
        // Operator found
        else if (isOperator(arrs[i])){
            while (
                precedence(arrs[i])
                < precedence(char_stack.top())) {
                output.push_back(char_stack.top());
                output.push_back(" ");
                char_stack.pop();
            }

                // Push current Operator on stack
                char_stack.push(arrs[i]);
        }else{
            //TO DO EXCEPTION
        }
    }
    while (!char_stack.empty()) {
        output.push_back(char_stack.top());
        output.push_back(" ");
        char_stack.pop();
    }
    output.pop_back();
    reverse(output.begin(),output.end());
    string result = "";
    for (unsigned int i = 0 ; i < output.size();i++){
        result += output[i];
    }
    return result;
}

string PostfixPrefixCalculator(string input){
    vector<string> arrs = splitfix(input);
    stack<string> num_stack;
    vector<string> output;
    stringstream s;
    s.precision(50);
    if (isdigit(arrs[0][0])){
        for (unsigned int i = 0; i<arrs.size(); i++){
            if(i == arrs.size() - 1){
                s.precision(11);
            }
            s.str("");
            string topstk =num_stack.empty()? "" :num_stack.top() ;
            if (isdigit(arrs[i][0])){
                num_stack.push(arrs[i]);
            }else{
                string num1str = num_stack.top();
                num_stack.pop();
                string num2str = num_stack.top();
                num_stack.pop();
                string typ = "int";
                if (num1str.find('.') != string::npos || num2str.find('.') != string::npos){
                    typ = "double";
                }
                if (arrs[i] == "+"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num1+num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num1+num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }
                }else if(arrs[i] == "-"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num2-num1;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num2-num1;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }
                }else if(arrs[i] == "*"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num1*num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num1*num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = to_string(result);
                        string re_str1 = s.str();
                        num_stack.push(s.str());
                    }
                }else if(arrs[i] == "/"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        if (num2 % num1 !=0){
                            long double n1 = stold(num1str);
                            long double n2 = stold(num2str);
                            long double result = n2/n1;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                            s<<result;
                            string re_str = s.str();
                            num_stack.push(re_str);
                        }else{
                            int result = num2/num1;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                            s<<result;
                            num_stack.push(s.str());
                        }
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num2/num1;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = s.str();
                        num_stack.push(re_str);
                    }
                }else if(arrs[i] == "^"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num2;
                        for (int i = 1; i<num1; i++){
                            result = result*num2;
                        }
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = s.str();
                        num_stack.push(re_str);
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num2;
                        for (int i = 1; i<num1; i++){
                            result = result*num2;
                        }
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = s.str();
                        num_stack.push(re_str);
                    }
                }
            }
        }
        return num_stack.top();
    }else{
        reverse(arrs.begin(),arrs.end());        
        for (unsigned int i = 0; i<arrs.size(); i++){
            if(i == arrs.size() - 1){
                s.precision(11);
            }
            s.str("");
            string topstk =num_stack.empty()? "" :num_stack.top() ;
            if (isdigit(arrs[i][0])){
                num_stack.push(arrs[i]);
            }else{
                string num1str = num_stack.top();
                num_stack.pop();
                string num2str = num_stack.top();
                num_stack.pop();
                string typ = "int";
                if (num1str.find('.') != string::npos || num2str.find('.') != string::npos){
                    typ = "double";
                }
                if (arrs[i] == "+"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num1+num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string res_str = s.str();
                        num_stack.push(s.str());
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num1+num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }
                }else if(arrs[i] == "-"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num1-num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num1-num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }
                }else if(arrs[i] == "*"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num1*num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        num_stack.push(s.str());
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num1*num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = s.str();
                        num_stack.push(re_str);
                    }
                }else if(arrs[i] == "/"){
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        if (num1 % num2 !=0){
                            long double num1f = stold(num1str);
                            long double num2f = stold(num2str);
                            long double result = num1f/num2f;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                            s<<result;
                            string re_str = s.str();
                            num_stack.push(re_str);
                        }else{
                            int result = num1/num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                            s<<result;
                            num_stack.push(s.str());
                        }
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num1/num2;
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = s.str();
                        num_stack.push(re_str);
                    }
                }else if(arrs[i] == "^"){                    
                    if (typ == "int"){
                        int num1 = stoi(num1str);
                        int num2 = stoi(num2str);
                        int result = num1;
                        for (int i = 1; i<num2; i++){
                            result = result*num1;
                        }
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = s.str();
                        num_stack.push(re_str);
                    }else{
                        long double num1 = stold(num1str);
                        long double num2 = stold(num2str);
                        long double result = num1;
                        for (int i = 1; i<num2; i++){
                            result = result*num1;
                        }
                        if(i == arrs.size() - 1){
                            result = round(result * 10000) / 10000;
                        }
                        s<<result;
                        string re_str = s.str();
                        num_stack.push(re_str);
                    }
                }
            }
        }
        return num_stack.top();
    }
    return "hi";
}

string LogicInfix2Postfix(string infix){
    vector<string> input = split_logic(infix);
    // for (unsigned int i = 0; i<input.size();i++){
    //     cout<<input[i]<<" ";
    // }
    // cout<<endl;
    string postfix = "";
    stack<string> stk ;
    for (unsigned int i = 0 ; i<input.size();i++){
        if(isalpha(input[i][0])){
            postfix += input[i];
        }else if (input[i] == "("){
            stk.push(input[i]);
        }else if (input[i] == ")"){
            while (!stk.empty() && stk.top() != "(") {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop(); 
        }else{
            while (!stk.empty() && logic_precedence(input[i]) <= logic_precedence(stk.top())) {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(input[i]);
        }
    }
    // While stack is not empty, pop and print operators
    while (!stk.empty()) {
        postfix += stk.top();
        stk.pop();
    }

    // Remove the trailing space
    if(postfix[postfix.size()-1] == ' '){
        postfix.pop_back();
    }
    return postfix;
}

string LogicInfix2Prefix(string infix){
    vector<string> input = split_logic(infix);
    reverse(input.begin(),input.end());
    for (unsigned int i =0 ; i< input.size();i++){
        if (input[i] == "(") {
            input[i] = ")";
        }
        else if (input[i] == ")") {
            input[i] = "(";
        }
    }
    input.push_back(")");
    input.insert(input.begin(),"(");

    stack<string> stk ;
    vector<string> output;
    for (unsigned int i = 0; i<input.size();i++){
        if(isalpha(input[i][0])){
            output.push_back(input[i]);
        }else if (input[i] == "("){
            stk.push(input[i]);
        }else if (input[i] == ")"){
            while(stk.top() != "("){
                output.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
        }else if (isLogicoperator(input[i])){
            while(logic_precedence(input[i]) < logic_precedence(stk.top())){
                output.push_back(stk.top());
                stk.pop();
            }
            stk.push(input[i]);
        }
    }
    while(!stk.empty()){
        output.push_back(stk.top());
        stk.pop();
    }
    reverse(output.begin(),output.end());
    string result = "";
    for (unsigned int i = 0; i<output.size();i++){
        result += output[i];
    }
    return result;
}
struct data{
    string name;
    bool value;
};
string LogicPostfixPrefixCalculator(string input,string varlue){
    vector<data> datalist ;
    unsigned int y = varlue.find_first_of("01");
    unsigned int i = 0;
    while(y < varlue.size()){
        if(varlue[y] == ' '){
            y++;
            i++;
        }else{
            data inpdata;
            inpdata.name = varlue.substr(i,1);
            inpdata.value = (varlue[y] == '1')? true:false;
            datalist.push_back(inpdata);
            y++;
            i++;
        }
    }
    //vector<string> inp = splitlogicfix(input);
    vector<string> inp;
    inp = splitlogicfix(input);
    stack<bool>stk;
    if (isalpha(inp[0][0])){
        //postfix
        for(i = 0; i<inp.size();i++){
            if(isalpha(inp[i][0])){
                bool to_push ;
                for (unsigned int j = 0;j<datalist.size();j++){
                    if(datalist[j].name == inp[i].substr(0,1)){
                        to_push = datalist[j].value;
                        break;
                    }
                    if (j == datalist.size()-1){
                        //TO DO exception
                    }
                }
                stk.push(to_push);

            }else if (isLogicoperator(inp[i])){
                if (inp[i] == "~") {
                    bool to_push = !stk.top();
                    stk.pop();
                    stk.push(to_push);
                }else if (inp[i] == "&") {
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = val1 && val2;
                    stk.push(to_push);
                }else if(inp[i] == "|"){
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = val1 || val2;
                    stk.push(to_push);
                }else if (inp[i] == "->"){
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = !val2 || val1;
                    stk.push(to_push);
                }else if (inp[i] == "<->"){
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = (!val2 || val1) && (!val1 || val2) ;
                    stk.push(to_push);
                }
            }else{
                //TO DO exception
            }
        }
    }else if (isLogicoperator(inp[0])){
        //prefix
        reverse(inp.begin(),inp.end());
        for(i = 0; i<inp.size();i++){
            if(isalpha(inp[i][0])){
                bool to_push ;
                for (unsigned int j = 0;j<datalist.size();j++){
                    if(datalist[j].name == inp[i].substr(0,1)){
                        to_push = datalist[j].value;
                        break;
                    }
                    if (j == datalist.size()-1){
                        //TO DO exception
                    }
                }
                stk.push(to_push);

            }else if (isLogicoperator(inp[i])){
                if (inp[i] == "~") {
                    bool to_push = !stk.top();
                    stk.pop();
                    stk.push(to_push);
                }else if (inp[i] == "&") {
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = val1 && val2;
                    stk.push(to_push);
                }else if(inp[i] == "|"){
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = val1 || val2;
                    stk.push(to_push);
                }else if (inp[i] == "->"){
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = !val2 || val1;
                    stk.push(to_push);
                }else if (inp[i] == "<->"){
                    bool val1 = stk.top();
                    stk.pop();
                    bool val2 = stk.top();
                    stk.pop();
                    bool to_push = (!val2 || val1) && (!val1 || val2) ;
                    stk.push(to_push);
                }
            }else{
                //TO DO exception
            }
        }
    }else{
        // TO DO exception
    }
    return stk.top() ? "TRUE":"FALSE";
}