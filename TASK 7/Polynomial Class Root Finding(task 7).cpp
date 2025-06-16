
///---- Polynomial Class and Root Finding ----///


#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

const double EPSILON = 1e-6; // Small tolerance for floating-point comparisons

// Class to represent a polynomial
class Polynomial {
    vector<double> coeffs; // coeffs[i] stores the coefficient of x^i

public:
    // Constructor that takes a list of coefficients
    Polynomial(const vector<double>& c) : coeffs(c) {}

    // Print the polynomial in standard form
    void print() const {
        for (int i = coeffs.size() - 1; i >= 0; --i) {
            if (coeffs[i] != 0) {
                cout << (coeffs[i] >= 0 && i != coeffs.size()-1 ? " + " : "")
                     << coeffs[i] << "x^" << i;
            }
        }
        cout << endl;
    }

    // Evaluate polynomial at given x using Horner’s method
    double evaluate(double x) const {
        double result = 0;
        for (int i = coeffs.size() - 1; i >= 0; --i)
            result = result * x + coeffs[i];
        return result;
    }

    // Return the derivative polynomial
    Polynomial derivative() const {
        vector<double> deriv;
        for (int i = 1; i < coeffs.size(); ++i)
            deriv.push_back(i * coeffs[i]);
        return Polynomial(deriv);
    }

    // Addition of two polynomials
    Polynomial operator+(const Polynomial& other) const {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
        for (int i = 0; i < coeffs.size(); ++i) result[i] += coeffs[i];
        for (int i = 0; i < other.coeffs.size(); ++i) result[i] += other.coeffs[i];
        return Polynomial(result);
    }

    // Subtraction of two polynomials
    Polynomial operator-(const Polynomial& other) const {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
        for (int i = 0; i < coeffs.size(); ++i) result[i] += coeffs[i];
        for (int i = 0; i < other.coeffs.size(); ++i) result[i] -= other.coeffs[i];
        return Polynomial(result);
    }

    // Multiplication of two polynomials
    Polynomial operator*(const Polynomial& other) const {
        vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0);
        for (int i = 0; i < coeffs.size(); ++i)
            for (int j = 0; j < other.coeffs.size(); ++j)
                result[i + j] += coeffs[i] * other.coeffs[j];
        return Polynomial(result);
    }

    // Find root using Newton-Raphson method
    double newtonRaphson(double guess, int max_iter = 1000) const {
        Polynomial deriv = derivative();
        double x = guess;
        for (int i = 0; i < max_iter; ++i) {
            double fx = evaluate(x);        // f(x)
            double dfx = deriv.evaluate(x); // f'(x)
            if (fabs(dfx) < EPSILON)
                throw runtime_error("Derivative too small. Try different guess.");
            double x_new = x - fx / dfx;    // Newton's formula
            if (fabs(x_new - x) < EPSILON)
                return x_new;
            x = x_new;
        }
        throw runtime_error("Did not converge.");
    }

    // Find root using Bisection method
    double bisection(double a, double b, int max_iter = 1000) const {
        double fa = evaluate(a);
        double fb = evaluate(b);
        if (fa * fb > 0)
            throw runtime_error("f(a) and f(b) must have opposite signs.");

        for (int i = 0; i < max_iter; ++i) {
            double mid = (a + b) / 2;
            double fmid = evaluate(mid);
            if (fabs(fmid) < EPSILON || fabs(b - a) < EPSILON)
                return mid;

            if (fa * fmid < 0) {
                b = mid; fb = fmid;
            } else {
                a = mid; fa = fmid;
            }
        }
        throw runtime_error("Did not converge.");
    }
};

// ----------- Main function to test Polynomial class -------------
int main() {
    Polynomial p1({-6, 11, -6, 1}); // Represents x^3 - 6x^2 + 11x - 6
    cout << "Polynomial p1: ";
    p1.print();

    // Create another polynomial 2x + 1
    Polynomial p2({1, 2});

    // Perform addition, subtraction, and multiplication
    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "\nSum: ";
    sum.print();
    cout << "Difference: ";
    diff.print();
    cout << "Product: ";
    prod.print();

    // Attempt to find roots using two methods
    try {
        double root1 = p1.newtonRaphson(3.5); // Guess close to x = 3
        cout << "\nNewton-Raphson root near 3.5: " << root1 << endl;

        double root2 = p1.bisection(0.0, 1.5); // Bracket near x = 1
        cout << "Bisection root in [0, 1.5]: " << root2 << endl;
    } catch (const exception& e) {
        cerr << "Root finding failed: " << e.what() << endl;
    }

    return 0;
}
