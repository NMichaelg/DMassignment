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
    if (infix.find(" ")){
        return "bitch";
    }
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

    for (int i = 0; i < expression.length(); i++) {
        string c ;
        c += expression[i];

        // If the character is a space, skip it
        if (isspace(c[0])) {
            continue;
        }

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
    stack<string> st;
    string result;
    for (unsigned int i = 0; i < arrs.size(); i++) {
        string c = arrs[i];
  
        // If the scanned character is
        // an operand, add it to output string.
        if (isdigit(c[0])){
            result += c;
            result += ' ';
        } 
        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (c == "(")
            st.push("(");
  
        // If the scanned character is an ‘)’,
        // pop and add to output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ")") {
            while (st.top() != "(") {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
  
        // If an operator is scanned
        else {
            while (!st.empty()
                   && precedence(arrs[i]) <= precedence(st.top())) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
  
    // Pop all the remaining elements from the stack
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    return result;
}