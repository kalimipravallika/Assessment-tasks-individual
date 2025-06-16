
///---- Monte Carlo Pi Estimation ----///


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

// Function to estimate the value of π using Monte Carlo method
double estimatePi(int samples) {
    int insideCircle = 0; // Counter for points inside the unit circle
    
    // Generate random points and check if they are inside the unit circle
    for (int i = 0; i < samples; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX; // Random x coordinate in [0,1]
        double y = static_cast<double>(rand()) / RAND_MAX; // Random y coordinate in [0,1]

        // Check if the point (x, y) falls inside the unit circle (x^2 + y^2 <= 1)
        if (x * x + y * y <= 1.0) {
            insideCircle++; // Increment counter if point is inside
        }
    }

    // π is estimated using the ratio of points inside the circle to total points
    return 4.0 * insideCircle / samples;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with current time

    const double actualPi = 3.141592653589793; // True value of π for comparison
    int sampleSizes[] = {100, 1000, 10000, 100000, 1000000}; // Different sample sizes for estimation

    // Formatting output to display numbers with six decimal places
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Monte Carlo Pi Estimation:\n\n";
    std::cout << "Samples\t\tEstimated Pi\tError\n";

    // Loop through different sample sizes and estimate π
    for (int samples : sampleSizes) {
        double estimatedPi = estimatePi(samples); // Call function to estimate π
        double error = std::abs(actualPi - estimatedPi); // Calculate error from actual value
        std::cout << samples << "\t\t" << estimatedPi << "\t\t" << error << "\n"; // Print results
    }

    return 0; // End program successfully
}
