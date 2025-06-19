
## Statistical Metrics Calculator in C++ ##

This C++ program calculates fundamental statistical metrics for a given dataset:  
- Mean (average)
- Median (middle value)
- Variance
- Standard Deviation

It uses a vector to store the data, performs calculations, and prints the results.

## Features 

- Uses C++ STL algorithms for efficiency (`std::sort`, `std::accumulate`).
- Supports dynamic datasets via vectors.
- Provides formatted output to display calculated statistics.

## How It Works 

1. **Mean Calculation**  
   - Uses the sum of all values divided by the total count.
   
2. **Median Calculation**  
   - Sorts the data and picks the middle value (or the average of two middle values if the size is even).
   
3. **Variance Calculation**  
   - Measures the spread of the data points from the mean.
   
4. **Standard Deviation Calculation**  
   - Square root of the variance, indicating the dispersion of values.

## How to run

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select C++ as the language.
3. Write the code.
4. Click "Run" to execute.

## Sample output 

Dataset: 45 20 9 24 16 

Mean: 22.8
Median: 20
Variance: 147.76
Standard Deviation: 12.1557





