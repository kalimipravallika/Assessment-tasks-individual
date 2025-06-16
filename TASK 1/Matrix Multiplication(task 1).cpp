///---- Matrix Multiplication Class----///

// Include necessary libraries
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// A generic Matrix class using templates (can store int, float, etc.)
template<typename T>
class Matrix {
private:
    vector<vector<T>> data; // 2D vector to hold matrix elements
    size_t rows, cols;      // number of rows and columns

public:
    // Default constructor: creates 0x0 empty matrix
    Matrix() : rows(0), cols(0) {}

    // Creates matrix with r rows and c columns
    Matrix(size_t r, size_t c, T initVal = T()) : rows(r), cols(c) {
        data.assign(r, vector<T>(c, initVal));
    }

    // Get number of rows and columns
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Access matrix elements using [row][col]
    vector<T>& operator[](size_t i) { return data[i]; }
    const vector<T>& operator[](size_t i) const { return data[i]; }

    // Add two matrices
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Incompatible dimensions for addition");

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                result[i][j] = data[i][j] + other[i][j];

        return result;
    }

    // Subtract two matrices
    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Incompatible dimensions for subtraction");

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                result[i][j] = data[i][j] - other[i][j];

        return result;
    }

    // Multiply two matrices
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows)
            throw invalid_argument("Incompatible dimensions for multiplication");

        Matrix<T> result(rows, other.cols, 0);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < other.cols; j++)
                for (size_t k = 0; k < cols; k++)
                    result[i][j] += data[i][k] * other[k][j];

        return result;
    }

    // Print matrix
    friend ostream& operator<<(ostream& os, const Matrix<T>& m) {
        if (m.rows == 0 || m.cols == 0) {
            os << "0x0 matrix\n";
            return os;
        }

        for (size_t i = 0; i < m.rows; i++) {
            for (size_t j = 0; j < m.cols; j++) {
                os << m[i][j];
                if (j < m.cols - 1) os << " ";
            }
            os << "\n";
        }

        return os;
    }
};

int main() {
    try {
        // Create and fill Matrix A and Matrix B (3x3)
        Matrix<int> A(3, 3), B(3, 3);
        int valA[3][3] = {{4,8,9},{2,5,6},{3,6,9}};
        int valB[3][3] = {{10,2,4},{8,1,3},{5,8,1}};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                A[i][j] = valA[i][j];
                B[i][j] = valB[i][j];
            }

        // Show addition, subtraction, multiplication
        cout << "Matrix A:\n" << A;
        cout << "\nMatrix B:\n" << B;
        cout << "\nMatrix A + B:\n" << (A + B);
        cout << "\nMatrix A - B:\n" << (A - B);
        cout << "\nMatrix A * B:\n" << (A * B);

        // Another multiplication with 2x3 and 3x2 matrix
        Matrix<int> C(2, 3), D(3, 2);
        int valC[2][3] = {{5,9,2},{4,1,0}};
        int valD[3][2] = {{1,5},{3,2},{4,6}};
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 3; j++)
                C[i][j] = valC[i][j];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++)
                D[i][j] = valD[i][j];

        cout << "\nMatrix C (2x3):\n" << C;
        cout << "\nMatrix D (3x2):\n" << D;
        cout << "\nMatrix C * D:\n" << (C * D);

        // Check with empty 0x0 matrices
        Matrix<int> E(0, 0), F(0, 0);
        cout << "\nEdge Case - Matrix with zero rows and cols:\n";
        cout << "Matrix E:\n" << E;
        cout << "\nMatrix F:\n" << F;
        cout << "\nMatrix E + Matrix F:\n" << (E + F);
        cout << "\nMatrix E * Matrix F:\n" << (E * F);

        // Invalid multiplication: should throw an exception
        Matrix<int> G(3, 3), H(2, 3);
        cout << "\nEdge Case - Invalid Multiplication:\n";
        Matrix<int> R = G * H;
        cout << R;
    }
    catch (const exception& e) {
        // Catch and show any error messages
        cout << "Exception caught: " << e.what() << endl;
    }

    return 0;
}
