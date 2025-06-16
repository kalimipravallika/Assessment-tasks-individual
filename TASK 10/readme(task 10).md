
## Monte Carlo π Estimation in C++ ##

This program estimates the value of π using the `Monte Carlo method`. The Monte Carlo technique relies on random sampling to approximate mathematical results—in this case, determining π by randomly placing points inside a unit square and checking how many fall within a unit circle.

## Features 

- Implements the Monte Carlo method for π estimation.
- Uses random number generation for sampling.
- Runs calculations for multiple sample sizes.
- Displays the `estimated value of π` and its `error` from the actual value.
- Outputs results in a `formatted table` with six decimal precision.


## How It Works 

1. Randomly generate (x, y) points in the range `[0, 1]`.
2. Check if each point lies inside the unit circle using the equation:
  x^2 + y^2 <= 1
3. Count the number of points inside the circle.
4. **Estimate π** using the ratio:
  π ≈ 4 × (points inside circle / total points)
5. The program repeats this process for various sample sizes to see how accuracy improves with more iterations.

 ## How to run

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output :

Monte Carlo Pi Estimation:

Samples		Estimated Pi	Error
100		3.240000		0.098407
1000		3.112000		0.029593
10000		3.141600		0.000007
100000		3.149520		0.007927
1000000		3.142008		0.000415

