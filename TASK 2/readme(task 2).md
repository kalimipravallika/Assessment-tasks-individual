
## Expression Evaluator (C++) ##

This project implements an infix expression evaluator in C++ that converts expressions into postfix notation (Reverse Polish Notation - RPN) and then evaluates them using a stack-based approach. It supports basic arithmetic operations: `+`, `-`, `*`, and `/`.

## Features 

- Converts infix expressions to postfix notation (RPN).
- Evaluates postfix expressions using a stack-based algorithm.
- Handles parentheses correctly to ensure precedence.
- Supports multi-digit numbers.
- Demonstrates exception handling for invalid expressions.

## How It Works

1. **Infix to Postfix Conversion**
- Uses a stack-based approach to transform expressions into postfix notation.
- Maintains operator precedence (`*` and `/` have higher precedence than `+` and `-`).
- Uses parentheses handling to process nested expressions.

2. **Postfix Evaluation**
- Uses a stack to store operands.
- Reads postfix notation token by token.
- If it's a number, pushes it onto the stack.
- If it's an operator, pops two numbers, applies the operation, and pushes the result.

3. **Expression Testing**
- Includes a set of predefined mathematical expressions.
- Converts and evaluates each expression to display the result.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output

Expression: 3 + (4 * 2)
Result: 11

Expression: (1 + 2) * 3
Result: 9

Expression: 25 + 2 * 6 + 9
Result: 46

Expression: 92 * 2 + 12
Result: 196

Expression: 100 * (2 + 12) / 14
Result: 100

