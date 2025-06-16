
///---- Numerical Integration ----///

#include <iostream>
#include <cmath>
#include <iomanip> // For formatting output with set precision

// Define the function f(x) = e^x
double f(double x) {
    return std::exp(x); // Built-in exponential function
}

// Trapezoidal Rule for numerical integration
double trapezoidal(double a, double b, int n) {
    double h = (b - a) / n;       // Step size
    double sum = f(a) + f(b);     // Endpoints counted once

    // Add 2 * f(x_i) for interior points
    for (int i = 1; i < n; ++i) {
        sum += 2 * f(a + i * h);
    }

    return (h / 2) * sum; // Final result
}

// Simpson's Rule for numerical integration
double simpson(double a, double b, int n) {
    if (n % 2 != 0) n++; // Simpson's Rule needs even number of intervals

    double h = (b - a) / n;
    double sum = f(a) + f(b); // Add endpoints

    // Alternate weights: 4 for odd-indexed, 2 for even-indexed points
    for (int i = 1; i < n; ++i) {
        if (i % 2 == 0)
            sum += 2 * f(a + i * h);
        else
            sum += 4 * f(a + i * h);
    }

    return (h / 3) * sum; // Final result
}

int main() {
    double a = 0.0, b = 1.0;         // Integration interval [a, b]
    double exact = 1.71828;          // Approximate true value of ∫e^x dx from 0 to 1
    int ns[] = {10, 100, 1000};      // Different numbers of intervals for testing

    std::cout << std::fixed << std::setprecision(5); // Format output to 5 decimal places

    // Loop through different values of n and compute results
    for (int n : ns) {
        double trap_result = trapezoidal(a, b, n);      // Trapezoidal rule result
        double simpson_result = simpson(a, b, n);       // Simpson's rule result
        double trap_error = std::abs(trap_result - exact);      // Error from exact
        double simpson_error = std::abs(simpson_result - exact);

        // Output results
        std::cout << "For n = " << n << ":\n";
        std::cout << "Trapezoidal Result = " << trap_result << ", Error = " << trap_error << '\n';
        std::cout << "Simpson's Result   = " << simpson_result << ", Error = " << simpson_error << "\n\n";
    }

    return 0;
}
