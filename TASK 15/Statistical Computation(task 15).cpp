
 ///---- Statistical Computation with Modern C++ ----///

#include <iostream>
#include <vector>
#include <algorithm> // For sorting the dataset to find the median
#include <cmath>     // For square root function used in standard deviation
#include <numeric>   // For accumulating sum in mean calculation

// Function to calculate mean (average)
double calculateMean(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0); // Sum all values
    return sum / data.size(); // Divide by number of elements to get mean
}

// Function to calculate median (middle value)
double calculateMedian(std::vector<double> data) {
    std::sort(data.begin(), data.end()); // Sort the dataset
    size_t n = data.size();
    
    // If number of elements is even, take average of middle two
    if (n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2;
    } else {
        return data[n / 2]; // If odd, take the middle element
    }
}

// Function to calculate variance
double calculateVariance(const std::vector<double>& data) {
    double mean = calculateMean(data); // Calculate mean first
    double sum = 0.0;
    
    // Sum squared differences from the mean
    for (auto value : data) {
        sum += (value - mean) * (value - mean);
    }
    
    return sum / data.size(); // Compute variance (for sample variance, use data.size() - 1)
}

// Function to calculate standard deviation
double calculateStdDev(const std::vector<double>& data) {
    return std::sqrt(calculateVariance(data)); // Standard deviation is square root of variance
}

int main() {
    std::vector<double> dataset = {45, 20, 9, 24, 16}; // Define dataset
    
    // Calculate statistical metrics
    double mean = calculateMean(dataset);
    double median = calculateMedian(dataset);
    double variance = calculateVariance(dataset);
    double stddev = calculateStdDev(dataset);

    // Display dataset
    std::cout << "Dataset: ";
    for (auto num : dataset) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // Display results
    std::cout << "Mean: " << mean << "\n"; // Print mean
    std::cout << "Median: " << median << "\n"; // Print median
    std::cout << "Variance: " << variance << "\n"; // Print variance
    std::cout << "Standard Deviation: " << stddev << "\n"; // Print standard deviation

    return 0; // End program successfully
}


