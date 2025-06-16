
///---- Expression Evaluator ---- ///

// Include necessary libraries for input/output, stacks, strings, and parsing
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <map>
using namespace std;

// Function to check if a character is an operator (+, -, *, /)
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to define the order of operations (precedence)
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression (normal math) to postfix (RPN)
string infixToPostfix(string expr) {
    stack<char> opStack;  // Stack to hold operators
    string postfix = "";  // Resulting postfix expression

    // Loop through each character of the expression
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (c == ' ') continue; // Skip spaces

        if (isdigit(c)) {
            // Add multi-digit numbers to the postfix string
            while (i < expr.length() && isdigit(expr[i])) {
                postfix += expr[i++];
            }
            postfix += ' ';
            i--; // Adjust for loop increment
        }
        else if (c == '(') {
            opStack.push(c); // Push opening bracket
        }
        else if (c == ')') {
            // Pop and add all operators until opening bracket is found
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.pop(); // Remove '('
        }
        else if (isOperator(c)) {
            // Maintain precedence and pop higher or equal operators
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(c); // Push current operator
        }
    }

    // Pop remaining operators
    while (!opStack.empty()) {
        postfix += opStack.top();
        postfix += ' ';
        opStack.pop();
    }

    return postfix;
}

// Function to evaluate a postfix (RPN) expression
int evaluatePostfix(string postfix) {
    stack<int> valStack;         // Stack to store intermediate values
    istringstream iss(postfix);  // Break string into tokens
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            valStack.push(stoi(token)); // Push numbers
        } else {
            int b = valStack.top(); valStack.pop();  // Second operand
            int a = valStack.top(); valStack.pop();  // First operand
            int result;
            // Apply the operator
            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") result = a / b;
            valStack.push(result);  // Push result back
        }
    }

    return valStack.top(); // Final answer
}

// Overall function: converts and then evaluates the expression
int evaluateExpression(string expr) {
    string postfix = infixToPostfix(expr);
    return evaluatePostfix(postfix);
}

// Main function to test expressions
int main() {
    string expressions[] = {
        "3 + (4 * 2)",
        "(1 + 2) * 3",
        "25 + 2 * 6 + 9",
        "92 * 2 + 12",
        "100 * (2 + 12) / 14"
    };

    for (string expr : expressions) {
        cout << "Expression: " << expr << endl;
        cout << "Result: " << evaluateExpression(expr) << endl << endl;
    }

    return 0;
}

