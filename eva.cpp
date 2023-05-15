#include "eva.h"
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
// Function to convert infix expression to postfix expression
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
// Function to conver infix to prefix
vector<string> splitExpression(string expression) {
    vector<string> tokens;
    string currentToken = "";

    for (unsigned int i = 0; i < expression.length(); i++) {
        string c ;
        c += expression[i];

        // If the character is a digit or a decimal point, add it to the current token
        if (isdigit(c[0])) {
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
        else {
            tokens.push_back(c);
        }
    }

    // Add the last token to the vector if it exists
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
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
        else {
            while (
                precedence(arrs[i])
                < precedence(char_stack.top())) {
                output.push_back(char_stack.top());
                output.push_back(" ");
                char_stack.pop();
            }

                // Push current Operator on stack
                char_stack.push(arrs[i]);
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