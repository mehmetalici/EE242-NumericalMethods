## Computation of Eigenvalues and Eigenvectors
Implementation of the normalized power iteration algorithm together with deflation to find two eigenvalues and corresponding eigenvector for the dominant eigenvalue of a given matrix A on C++

### Getting Started
#### Prerequisites
1. C++ compiler capable of C++11 or above. 

#### Installing
Assuming you use `g++`,
1. g++ source.cpp -std=c++11 -o eig-things

#### Running
The program has three command line arguments for the parameters:
1. Path to the file you read the matrix from,
2. Tolerance used in the normalized power iteration algorithm,
3. Name of your output file.

For example, given:

A.txt
```
1 2
3 4
```

Tolearance=0.0001, and path to the output file ./out.txt, running the program:

`./eig-things A.txt 0.00001 out.txt`

yields the following output:
```
Eigenvalue #1: 5.37

Eigenvector #1: 
0.46  
1.00  

Eigenvalue #2: 
-0.37


out.txt is successfully created!
```
Checking the contents of out.txt, yields:

```
Eigenvalue #1: 
5.37

Eigenvector #1: 
0.46
1.00

Eigenvalue #2: 
-0.37
```

### Design Decisions
A Matrix class was created to encapsulate its matrix operations. 

The calc_eigenThings() method computes the "eigen-things" of the corresponding matrix. The eigen-things corresponds to two eigen values together with the eigen vector for the dominant eigen value. 

















