# Gaussian Elimination with Partial Pivoting
Implementation of Gaussian elimination algorithm with partial pivoting together with backward substitution to solve Ax = b on C++

**Note: The program’s scope for determining condition number is limited to 2x2 matrices. You can find detailed information at “Arguments & Issues” section.**


### How to Run "source.cpp"
“source.cpp” is written in C++. You can use any compiler as you wish. Dev-C++, with TDM-GCC 4.9.2 compiler is tested and recommended.   


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

I have implemented our Gaussian Elimination algorithm with Partial Pivoting together with backward substition to solve Ax = b, where A is an n by n square matrix. The program reads A and b from two input files and output the solution x as a text file.  
#### The important points
The program yields an error and terminates running on two cases;
Firstly,if A and b’s inner dimensions does not agree, then the program gives an error for wrong inputs and requires to user to edit it and rerun the program.
Secondly, an error quit if it detects that A is singular, the machine precision is considered while detecting singularity and set to 1E-6.



