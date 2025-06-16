
### Polynomial Class in C++ ###

This project implements a Polynomial class in C++ that supports various operations such as addition, subtraction, multiplication, evaluation, and differentiation. It also provides methods to find roots using `Newton-Raphson and Bisection methods`.

## Features

- Construct polynomials from a list of coefficients.
- Perform arithmetic operations: addition, subtraction, multiplication.
- Evaluate polynomials using Horner’s method.
- Compute derivatives of polynomials.
- Find polynomial roots using:
  - `Newton-Raphson method` (fast but requires a good initial guess).
  - `Bisection method` (requires an interval with opposite signs).

## How It Works

1. **Polynomial Representation**
- Stored as a vector of coefficients, where index `i` corresponds to the coefficient of `x^i`.
- Supports printing in readable format.

2. **Arithmetic Operations**
- Addition (`operator+`) → Adds corresponding coefficients.
- Subtraction (`operator-`) → Subtracts corresponding coefficients.
- Multiplication (`operator*`) → Uses nested loops to compute product terms.

3. **Root Finding**
- `Newton-Raphson Method`:
  - Uses the formula:
    x_new = x - f(x) / f'(x)
  - Iterates until convergence or throws an exception if it does not converge.
- `Bisection Method`:
  - Requires an interval `[a, b]` where `f(a) * f(b) < 0`.
  - Repeatedly divides the interval until a root is found.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output

Polynomial p1: 1x^3-6x^2 + 11x^1-6x^0

Sum: 1x^3-6x^2 + 13x^1-5x^0
Difference: 1x^3-6x^2 + 9x^1-7x^0
Product: 2x^4-11x^3 + 16x^2-1x^1-6x^0

Newton-Raphson root near 3.5: 3
Bisection root in [0, 1.5]: 1

