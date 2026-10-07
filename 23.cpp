#include <iostream>                         //for cin cout
#include <string>                           //for string expressions
#include <stack>                            //for LIFO approach
#include <cctype>                           //to use utility functions like isalnum() to test alphanumeric char
#include <algorithm>                        //to use reverse func

using namespace std;

bool isOperator(char c) {                   //helper function to check operator 
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {                   //helper function to return priority order of operator
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

string infixToPostfix(const string &infix) {                //accepts an infix string and returns its postfix
    string postfix = "";
    stack<char> opStack;                                    //char type operator stack to temporarily hold operator and parenthesis

    for (char c : infix) {                                  //for loop to process input expression char by char from left to right
        if (isalnum(c)) {                                   //check whether char c is an operand                          
            postfix += c;                                   //operands pass to output string without entering stack
        } 
        else if (c == '(') {                                //to check openining parenthesis encountered or not
            opStack.push(c);                                //yes, then push to opStack(The temporary Operator stack to hold operators such as '+', '-')
        } 
        else if (c == ')') {                                //triggered when closing parenthesis reached
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty()) {
                opStack.pop();                              // Remove '('
            }
        } 
        else if (isOperator(c)) {
            // For right-associative '^', change >= to > if strict exponentiation handling is required
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }

    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}

string infixToPrefix(const string &infix) {
    string reversedInfix = "";
    
    //Reverse string and swap parentheses
    for (int i = infix.length() - 1; i >= 0; i--) {
        if (infix[i] == '(') {
            reversedInfix += ')';
        } else if (infix[i] == ')') {
            reversedInfix += '(';
        } else {
            reversedInfix += infix[i];
        }
    }

    //Convert modified infix to postfix with prefix precedence rules
    string reversedPostfix = "";
    stack<char> opStack;

    for (char c : reversedInfix) {
        if (isalnum(c)) {
            reversedPostfix += c;
        } 
        else if (c == '(') {
            opStack.push(c);
        } 
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                reversedPostfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty()) {
                opStack.pop(); // Remove '('
            }
        } 
        else if (isOperator(c)) {
            while (!opStack.empty() && opStack.top() != '(') {
                int p1 = precedence(opStack.top());
                int p2 = precedence(c);

                // For reversed prefix string:
                // Left-associative (+,-,*,/) use strictly >
                // Right-associative (^) uses >=
                if ((c == '^' && p1 >= p2) || (c != '^' && p1 > p2)) {
                    reversedPostfix += opStack.top();
                    opStack.pop();
                } else {
                    break;
                }
            }
            opStack.push(c);
        }
    }

    while (!opStack.empty()) {
        reversedPostfix += opStack.top();
        opStack.pop();
    }

    //Reverse postfix to get final prefix expression
    string prefix = reversedPostfix;
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

int main() {
    string infix;
    cout << "Enter the infix expression: ";
    getline(cin, infix);                            //getline to read entire line of expression including spaces

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix expression: " << postfix << endl;
    cout << "Prefix expression: " << prefix << endl;

    return 0;
}