---------------------------------------
Project 3- Secant and Bisection Methods
---------------------------------------
Implementation of secant and bisection algorithms in order to solve f(x) = 0 for any given polynomial f.
----------------------
Command Line Arguments
-----------------------
The program takes the coefficients of the function, initial guesses and the tolerance value as command line arguments.

-----------------------
How to Run "source.cpp"
-----------------------
“source.cpp” is written in C++. You can use any compiler as you wish. Dev-C++, with TDM-GCC 4.9.2 compiler is tested and recommended.

----------------
Design Decisions
-----------------
To achieve project goals I have created a matrix class and implemented the algorithms as class member functions. As they iterate until they converges, I prefered them to be recursive functions. I made my decisions with regard to simplicity and flexibility. Thus, the program is open to further developments.

With this design methodology, you can try hybrid method with various combinations of iterations of secant and bisection methods as you wish. You can achieve this by tinkering with the 3rd parameters of class methods. For example: 
getRootbySec(guess1, guess2, 6) will iterate 3 times and likewise getRootbyBisec(guess1*, guess2*, 7) will iterate 7 times. 3rd parameters are default so without them, they will go until convergence.

guess1*, guess2*: they can be Function.getx0() and Function.getx1() if we want to alternate the methods. 
