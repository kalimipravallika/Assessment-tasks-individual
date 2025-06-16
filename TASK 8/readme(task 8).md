
## Numerical Integration in C++ ##

This project implements numerical integration techniques in C++ using `Trapezoidal Rule` and `Simpson's Rule` to approximate the integral of `f(x) = e^x` over a given interval `[a, b]`. The program calculates results for different numbers of intervals (`n`) and compares the error against an approximate exact value.

## Features

- Implements Trapezoidal Rule for numerical integration.
- Implements Simpson's Rule for better accuracy.
- Evaluates the integral of `f(x) = e^x` over `[0, 1]`.
- Compares results for different interval counts (`n = 10, 100, 1000`).
- Displays errors from the approximate exact integral value (`∫e^x dx from 0 to 1 ≈ 1.71828`).

## How It Works

1. **Trapezoidal Rule**
- Approximates the integral by summing trapezoidal areas under the curve.

2. **Simpson's Rule**
- Uses a weighted sum to provide a more accurate estimate.

3. **Error Calculation**
- Compares each result with the approximate exact value `1.71828`.
- Displays the difference to highlight accuracy.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output

For n = 10:
Trapezoidal Result = 1.71971, Error = 0.00143
Simpson's Result   = 1.71828, Error = 0.00000

For n = 100:
Trapezoidal Result = 1.71830, Error = 0.00002
Simpson's Result   = 1.71828, Error = 0.00000

For n = 1000:
Trapezoidal Result = 1.71828, Error = 0.00000
Simpson's Result   = 1.71828, Error = 0.00000

