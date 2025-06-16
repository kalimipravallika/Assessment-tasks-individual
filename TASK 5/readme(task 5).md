
### Lock-Free Smart Pointer (C++) ###

This project implements a custom lock-free smart pointer(`LockFreeSharedPtr`) using atomic reference counting in C++. It compares the performance of standard `std::shared_ptr` vs. the custom implementation by conducting multithreaded stress tests and benchmarking.

## Features

- Custom atomic reference counting for a smart pointer.
- Lock-free memory management, avoiding mutexes for performance.
- Multithreaded stress testing of smart pointer copying.
- Benchmark comparison with `std::shared_ptr`.

## How It Works

1. **Custom Lock-Free Smart Pointer**
- Uses an internal control block containing:
  - A `raw pointer` to the object.
  - An `atomic reference counter` for thread-safe management.
- Implements:
  - Reference counting updates using atomic operations (`fetch_add` and `fetch_sub`).
  - Automatic memory cleanup when the last reference is released.

2. **Multithreaded Stress Test**
- Creates multiple copies of smart pointers across 8 threads.
- Randomly `shuffles copies` to simulate real-world usage.
- Validates `thread safety` by preventing race conditions.

3. **Benchmarking vs. `std::shared_ptr`**
- Measures execution time for creating and copying smart pointers.
- Runs parallel pointer allocation across multiple threads.
- Compares performance with `std::shared_ptr` under identical conditions.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output

=== Stress Testing Lock-Free Smart Pointer ===
Stress test completed successfully.

=== Benchmarking ===
LockFreeSharedPtr Time: 0.0972661 seconds
std::shared_ptr Time: 0.10193 seconds