
### Concurrent Merge Sort in C++ ###

This project implements and benchmarks a parallel merge sort using `std::async` in C++. The program compares the performance of sequential and concurrent merge sort on large datasets ranging from `1 million to 10 million elements`.

## Features

- Standard (sequential) merge sort implementation.
- Multithreaded merge sort using `std::async` for parallel execution.
- Benchmarking mechanism to measure execution time.
- Automatic random data generation for testing.

## How It Works

1. **Merge Sort Algorithm**
  - Sequential Merge Sort:
  - Uses traditional recursion to divide and conquer.
  - Merges sorted halves using a helper function.
  - Concurrent Merge Sort:
  - Uses `std::async` to parallelize sorting of left and right halves.
  - Waits for left side to complete before merging.

2. **Benchmarking**
- Generates random test data using C++11 random functions.
- Measures execution time using `std::chrono`.
- Compares sequential vs. concurrent execution times.

3. **Data Generation**
- Uses Mersenne Twister (`std::mt19937`) for repeatable random number generation.
- Generates numbers in the range `1 to 1,000,000`.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output

Generating data...

Benchmarking on 1 million elements:
Sequential Merge Sort (1M) took 3.40631 seconds
Concurrent Merge Sort (1M) took 1.59032 seconds

Benchmarking on 5 million elements:
Sequential Merge Sort (5M) took 19.7651 seconds
Concurrent Merge Sort (5M) took 11.9724 seconds

Benchmarking on 10 million elements:
Sequential Merge Sort (10M) took 29.1785 seconds
Concurrent Merge Sort (10M) took 18.064 seconds