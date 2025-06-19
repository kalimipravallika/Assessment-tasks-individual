
### Vector Class in C++ ###

This project implements a `generic N-dimensional vector class` using C++ templates. The class supports common vector operations such as addition, scalar multiplication, dot product, cross product (for 3D vectors), and normalization.

## Features 

- Template-based vector class supporting multiple dimensions
- Basic `arithmetic operations`: Addition and scalar multiplication
- `Dot product` for any N-dimensional vector
- `Cross product` (only for 3D vectors)
- `Vector norm` (magnitude) computation
- `Normalization` (converting to a unit vector)
- `Simple print function` to display vector elements

## How It Works 

1. **Defining the Vector Class**
- The `Vector<T, N>` class is template-based, meaning it can work with any data type (`T`) and any number of   dimensions (`N`).
- Internally, it stores the vector components in an `std::array<T, N>`.

2. **Vector Operations**
- Addition (`operator+`) 
  Each component of one vector is added to the corresponding component of another vector.

- Scalar Multiplication (`operator*`) 
  Each component of the vector is multiplied by a given scalar value.

- Dot Product (`dot`)  
  The dot product is computed by multiplying corresponding components and summing the results.
  
- Cross Product (`cross`) 
  Only applicable for **3D vectors** (`N == 3`).

- Norm ('Magnitude')
  The norm or magnitude of a vector represents its length in space.

- Normalization :
  A normalized vector (also called a unit vector) is a vector that points in the same direction but has a magnitude of 1.
 
  ## How to run

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

  ## Sample output 

v1 = (5, 7, 2)
v2 = (8, 9, 4)
v1 + v2 = (13, 16, 6)
v1 * 2 = (10, 14, 4)
v1 . v2 = 111
v1 x v2 = (10, -4, -11)
||v1|| = 8.83176
v1 normalized = (0.566139, 0.792594, 0.226455)
