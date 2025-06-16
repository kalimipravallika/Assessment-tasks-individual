
///---- Vector Algebra Library ----///

#include <iostream>
#include <array>
#include <cmath>
#include <cassert>
using namespace std;

// Template class for an N-dimensional vector
template<typename T, size_t N>
class Vector {
private:
    array<T, N> data; // Stores the vector elements

public:
    // Default constructor initializes all values to zero
    Vector() { data.fill(T{}); }

    // Constructor that initializes values from a list
    Vector(const initializer_list<T>& list) {
        assert(list.size() == N); // Ensure correct size
        size_t i = 0;
        for (T val : list) data[i++] = val;
    }

    // Allows accessing elements with indexing
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    // Adds two vectors element-wise
    Vector<T, N> operator+(const Vector<T, N>& other) const {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i)
            result[i] = data[i] + other[i];
        return result;
    }

    // Multiplies vector by a scalar
    Vector<T, N> operator*(T scalar) const {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i)
            result[i] = data[i] * scalar;
        return result;
    }

    // Computes dot product between two vectors
    T dot(const Vector<T, N>& other) const {
        T result = T{};
        for (size_t i = 0; i < N; ++i)
            result += data[i] * other[i];
        return result;
    }

    // Computes cross product (only for 3D vectors)
    Vector<T, 3> cross(const Vector<T, 3>& other) const {
        static_assert(N == 3, "Cross product is defined only for 3D vectors.");
        return Vector<T, 3>{
            data[1] * other[2] - data[2] * other[1],
            data[2] * other[0] - data[0] * other[2],
            data[0] * other[1] - data[1] * other[0]
        };
    }

    // Computes the magnitude (norm) of the vector
    double norm() const {
        T sum = T{};
        for (T val : data) sum += val * val;
        return sqrt(sum);
    }

    // Returns a normalized (unit) version of the vector
    Vector<T, N> normalize() const {
        double n = norm();
        assert(n != 0 && "Cannot normalize zero vector."); // Prevent division by zero
        return (*this) * (1.0 / n);
    }

    // Prints the vector in (x, y, z) format
    void print() const {
        cout << "(";
        for (size_t i = 0; i < N; ++i)
            cout << data[i] << (i < N - 1 ? ", " : "");
        cout << ")";
    }
};

// ---------- Test Cases ----------
int main() {
    Vector<double, 3> v1{5.0, 7.0, 2.0}; // Define a 3D vector
    Vector<double, 3> v2{8.0, 9.0, 4.0}; // Define another 3D vector

    cout << "v1 = "; v1.print(); cout << endl;
    cout << "v2 = "; v2.print(); cout << endl;

    // Test vector addition
    auto sum = v1 + v2;
    cout << "v1 + v2 = "; sum.print(); cout << endl;

    // Test scalar multiplication
    auto scaled = v1 * 2.0;
    cout << "v1 * 2 = "; scaled.print(); cout << endl;

    // Test dot product
    double dot = v1.dot(v2);
    cout << "v1 . v2 = " << dot << endl;

    // Test cross product
    auto cross = v1.cross(v2);
    cout << "v1 x v2 = "; cross.print(); cout << endl;

    // Test norm and normalization
    cout << "||v1|| = " << v1.norm() << endl;
    auto unit = v1.normalize();
    cout << "v1 normalized = "; unit.print(); cout << endl;

    return 0; // Successful execution
}
