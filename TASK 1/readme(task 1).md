
### Matrix Operations in C++ ###

This project implements a template-based matrix class in C++ that supports various operations such as addition, subtraction, and multiplication. 

## Features 

- Template-based matrix class for handling various data types.
- Supports matrix addition, subtraction, and multiplication.
- Exception handling for invalid operations (e.g., incompatible matrix dimensions).
- Overloaded operators (`+`, `-`, `*`, `<<`) for easy matrix computation.
- Edge case handling for empty matrices (`0x0`).
- Uses standard C++ STL containers (`std::vector`) for matrix storage.

## How It Works 

1. **Matrix Class Implementation**
- Uses a 2D vector (`std::vector<std::vector<T>>`) for matrix storage.
- Supports dynamic creation based on user-defined rows/columns.
- Provides operator overloading for arithmetic operations.

2. **Matrix Arithmetic**
- Addition (`operator+`) → Adds corresponding elements.
- Subtraction (`operator-`) → Subtracts corresponding elements.
- Multiplication (`operator*`) → Implements matrix multiplication using nested loops.

3. **Edge Case Handling**
- Handles empty matrices (`0x0`).
- Includes invalid multiplication scenario where rows/columns mismatch.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output 

Matrix A:                
4 8 9                      
2 5 6                      
3 6 9                     

Matrix B:
10 2 4
8 1 3
5 8 1

Matrix A + B:
14 10 13
10 6 9
8 14 10

Matrix C (2x3):
5 9 2
4 1 0

Matrix D (3x2):
1 5
3 2
4 6

Matrix C * D:
40 55
7 22

Edge Case - Matrix with zero rows and cols:
Matrix E:
0x0 matrix

Matrix F:
0x0 matrix

Matrix E * Matrix F:
0x0 matrix


