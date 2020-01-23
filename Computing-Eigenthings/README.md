# Computation of Eigenvalues and Eigenvectors
Implementation of the normalized power iteration algorithm together with deflation to find two eigenvalues and corresponding eigenvector for the dominant eigenvalue of a given matrix A on C++

----------------------
Command Line Arguments
----------------------
The program has three command line arguments for the parameters. The first argument is the name of the file you read the matrix from, the second argument is the tolerance, which will be used in the normalized power iteration algorithm, and the third argument is the name of your output file.


------------------
Design Decisions
------------------

This program computes Eigenvalues and Eigenvectors using Normalized Power Iteration together with Deflation. This program contains many matrix operations thus I decided to create a matrix class and implement all the operations. 

The calc_eigenThings() method computes the eigen things of the corresponding matrix. Since I was going to use the algorithm I mentioned above I decided this function to be a recursive function, i.e call itself until the conditions are met, to find the eigenthings of the given matrix. 

After finding, I decided to remove the eigenthings and create a new matrix B from A. Then call the same function calc_eigenThings() for matrix B. This operation yields the second eigenthings for the matrix A. 

Same prodecure can be followed to obtain further eigenthings of the matrix A.


















