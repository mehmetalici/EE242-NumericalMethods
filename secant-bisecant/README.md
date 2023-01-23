## Project 3- Secant and Bisection Methods
Implementation of secant and bisection algorithms in order to solve f(x) = 0 for any given polynomial f.

The program contains an additional hybrid method. It starts with the bisection method and iterates for a specific number of times, defined in `it_bisec` variable. Afterwards, it continues until convergence with the secant method to find a root. 

### Getting Started
#### Prerequisites
1. C++ compiler that can compile C++11 or above. 

#### Installing
Assuming you use `g++`,
1. g++ main.cpp -std=c++11 -o sec-bisec

#### Running
Run the executable with command-line arguments following the format below:

`./sec-bisec {coefficients} {guess 1} {guess 2} {tolerance}`

For example:
```bash
# Equation: x² + 100x + 100; Coefficients= [1, 100, 100]
# Guess 1: 10
# Guess 2: -3
# Tolerance 1e-5
./sec-bisec 1 100 100 10 -3 0.00001
```
yields the following result:
```
Root: -1.01021
# of Iterations: 4

The Bisection Method
Root: -1.0102
# of Iterations: 20

A Hybrid Method with a combination of the two
Root: -1.01021
# of Iterations: 6
```






