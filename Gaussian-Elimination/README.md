## Gaussian Elimination with Partial Pivoting
Implementation of Gaussian elimination algorithm with partial pivoting together with backward substitution to solve Ax = b on C++.

**Note: The program’s scope for determining condition number is limited to 2x2 matrices. You can find detailed information at “Arguments & Issues” section.**

### Getting Started
#### Prerequisites
1. C++ compiler capable of C++11 or above. 

#### Installing
Assuming you use `g++`,
1. g++ main.cpp -std=c++11 -o gaussian-elm

#### Running
Create two text files named `A.txt` and `b.txt` on the same directory with `source.cpp`, corresponding to the matrix A and vector b, respectively. Running `gaussian-elm` would output `x.txt` corresponding the solution vector. 

For example, given on the root directory:

A.txt 
```
1 2 
3 4
```

b.txt
```
0.5
0.1
```
Running `./gaussian-elm` yields the following result:

```
Matrix A obtained from text file:
1  2  
3  4  

Vector b is: 
0.5
0.1
Condition Number of matrix A at 1: 21
Condition Number of matrix at Infinity: 21


Upper-Triangularized U Matrix:
3  4  
0  0.666667  

Vector y, where U * x = y:
0.1
0.466667

Vector x, where A * x = b:
-0.9
0.7

x.txt file is successfully created on the project folder!
```

Checking the generated `x.txt` file would yield the expected content below:

x.txt
```
-0.9
0.7
```

### Arguments & Issues
In order not to add a great amount of burden onto this project, the condition number algorithm is only implemented for 2 x 2 matrices and it output the condition numbers at 1 and infinity. The conditions are printed at console.  Matrices with high condition numbers can cause issues, consider the following example:

```
A:
1.000 1.000
1.000 1.001

Condition Numbers of matrix A at 1 and inf: 4003.81

b1:             b2:
2.000           2.000
2.000           2.001

x1:              x2:
2                1.00012
-1.12104e-041    0.999881
```

The condition number yields an error bound for computed solution to linear system and it is noticed that the condition number of matrix A is 4003.81, so high that it is called as “ill-conditioned” or “nearly singular”. Therefore, it is noticed that an infinitesimal change in the input vector b causes a huge shift in vector x. 


### Design Procedure

Gaussian Elimination algorithm was implemented with Partial Pivoting together with backward substition to solve Ax = b, where A is an n by n square matrix. The program reads A and b from two input files and output the solution x as a text file.  

#### Things to Note
The program yields an error and terminates running on two cases;
1. If A and b’s inner dimensions does not agree, then the program gives an error for wrong inputs and requires to user to edit it and rerun the program.
2. If A is singular, the machine precision is considered while detecting singularity and set to 1E-6.



