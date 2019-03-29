#include <string>
#include <iostream>
#include <fstream>
#include<cmath>
using namespace std;

/* This program implements the Gaussian elimination algorithm with partial 
pivoting together with backward substitution to solve Ax = b, where A is an 
n by n square matrix. The program reads A and b from two input files and output 
the solution x as a text file.
*/

const float MACH_PRECISION = 1E-6;  //Initailize the machine precision number.


int main() {
	
	/**************************************************************************
	*	PART1																  *
	*	Obtaining the nxn A matrix and b vector from the text files.		  *
	*																		  *
	*                                                                         *																		
	***************************************************************************/
	
	int n1 = 0,n2 = 0; // n1 and n2 are the sizes of the A matrix and b vector, respectively.
	
	// required codes for fire I/O
	string line; // variable to read lines from text files.
	fstream afile ("a.txt"); //text of Matrix A is kept at afile variable. 
	fstream bfile("b.txt"); // likewise, vector b for bfile.

	
	if(afile.is_open()) {  //If text possessing matrix A can be opened successfully,
		
		while (getline (afile,line)) { //Until the end of the text is reached,
			n1++; // Count lines in order to get the rowNumber of A matrix.
		}
		afile.close(); // Close the file safely after the operation to avoid unwanted errors.
	}
	
	
	//Same process for b vector.
	if(bfile.is_open()) {
		
		while (getline (bfile,line)) {
			n2++;
		}
		bfile.close();
	}
	else {
		cout << "Error, file couldn't opened.";
	}
	
	int n;
 	if(n1 == n2) { // if matrix A's and vector b's rows are same,
		n = n1; // they are equalized to common variable n.
	}
	else {
		cout << "Matrix rows must agree"; // Wrong input error.
		return -1; // The program terminates  
	}
	
	
	
	/**************************************************************************
	*	PART2																  *
	*	Having obtained A and b, the program will form                        *
	*	matrix a and vector b via allocating dynamic memory .		          *
	*                                                                         *																		
	***************************************************************************/
		
	float ** a; //initilazing 2Dimensional array with dynamic memory. 
	a = new float* [n]; // There is a second dimension. n being the matrix rows.
	for(int i=0; i<n; i++) {
		a[i] = new float[n]; // initializing this second dimension with a for loop.
	}						 
	
	
	afile.open("a.txt"); // Reopen the a file to pass the values to the created matrix.
	// Passing values with a nested for loop since it's 2D.
	for(int i = 0; i<n; i++){  
		for(int j=0; j<n; j++) {
			afile >> a[i][j]; // It resembles cin. 
		}
	}
	
	//Printing the matrix A to consol to check.
	cout << "Matrix A obtained from text file:" << endl;
	for(int i = 0; i<n; i++){
		for(int j=0; j<n; j++) {
			cout << a[i][j] << "  "; //Nested for loop to print. Three spaced. 
		}
		cout << endl;
	}
	
	//Initializing b vector with dynamic memory.
	float *b;
	b = new float [n]; // n being the vector rows.
	
	
	bfile.open("b.txt"); //b file is opened,
	for(int i = 0; i<n; i++) { 
		bfile >> b[i];	 // and b vector is filled with the values in bfile.
	}
	
	bfile.close(); // closed to avoid errors.
	
	cout << endl <<  "Vector b is: " << endl;
	for(int i = 0; i<n; i++){
		cout << b[i] << endl; //Printing the vector b to the console.
	}
	
	
	//Finding condition number to check if the matrix ill or well conditioned.
	if(n==2) // To ease the process, the program finds only 1st and final condition of 2by2 matrices.
	{	
		double detA = (a[0][0]*a[1][1]) - (a[0][1]*a[1][0]); // determinant of 2 by 2 matrix.
		double normOne = (abs(a[0][0])+abs(a[1][0])) > (abs(a[0][1]) + abs(a[1][1])) ? (abs(a[0][0]) + abs(a[1][0])):(abs(a[0][1])+abs(a[1][1]));		//1st Norm
		double normIn = (abs(a[0][0]) +abs(a[0][1]) ) > (abs(a[1][0]) +abs(a[1][1]) ) ? (abs(a[0][0]) +abs(a[0][1]) ) : (abs(a[1][0]) +abs(a[1][1]));	//infinity norm.
		double normInv1 = (abs(a[1][1]/detA)+abs(a[1][0]/detA)) > (abs(a[0][1]/detA)+abs(a[0][0]/detA))? (abs(a[1][1]/detA)+abs(a[1][0]/detA)):(abs(a[0][1]/detA)+abs(a[0][0]/detA));	// 1st norm of inverse
		double normInvInf = (abs(a[1][1]/detA)+abs(a[0][1]/detA)) > (abs(a[1][0]/detA)+abs(a[0][0]/detA))? (abs(a[1][1]/detA)+abs(a[0][1]/detA)):(abs(a[1][0]/detA)+abs(a[0][0]/detA)); //Inf Norm of Inverse
		double cond1 = normOne  * normInv1; //condition nubmer of 2by2 matrix for the 1st norm is determined.
		double condInf = normIn * normInvInf; //condition nubmer of 2by2 matrix for the infinity norm is determined.
		cout << "Condition Number of matrix A at 1: " <<  cond1 << endl; //Prints the result to console. 
		cout << "Condition Number of matrix at Infinity: " << condInf << endl << endl; //Prints the result to console.
	}
	
	
	/**************************************************************************
	*	PART 3																  *
	*	Having formed A and b, the program will implement Gaussian Elimination*
	*	with partial pivoting.		                                          *
	*                                                                         *																		
	***************************************************************************/
	
		
	int highestAbsValIndex; // this variable will keep the entry having the highest absolute value and will play a crucial role in determining pivots. 
	
	
	for(int c = 0; c<n; c++) { //First leg of the nested for loop to circulate matrix A, with a dummy variable c.
	float highestAbsVal = abs(a[c][c]); // Highest absolute value is initialized to diagonals, and it will later be compared with subpivots. 
 
 
 
	/**************************************************************************
	*	PART 3 - Section a : PARTIAL PIVOTING								  *
	*	I have implemented partial pivoting and Gaussian elimination under the*
	*   first leg of the nested for loop.                                     *																		
	***************************************************************************/
		
		
		for(int r= c+1; r<n; r++) { //Second leg of the nested for loop, notice the initialization of r to c+1, to obtain subdiagonals.
			//PERMUTATION TIME !
			if( abs(a[r][c]) > highestAbsVal) { //If absolute value of subdiagonals happens to be more than the diagonal entry,  
				highestAbsVal = abs(a[r][c]); // Highest abs value becomes that subdiagonal.
				highestAbsValIndex = r; //and its index is kept.. 
				float tempA, tempB; //These dummy variables are used to change rows of the matrix A. 
				for(int k= 0; k<n; k++) { //A for loop to circulate the columns of A and do the change entry by entry.
					tempA = a[c][k]; // this is sooo stereotype :)
					a[c][k] = a[highestAbsValIndex][k];
					a[highestAbsValIndex][k] = tempA; // finished, huh!
				}
				tempB = b[highestAbsValIndex]; // and also gets mind-bending after a while :)
				b[highestAbsValIndex] = b[c]; 
				b[c] = tempB; // Good bye row change !
				
			}		
		}
		if(abs(highestAbsVal) < MACH_PRECISION) { // This part is very important in numerical computing. 
												  //If the created pivot after the for loop is beyond the machine precision number, which is 1E-6, the pivot will be considered as 0, and become singular.
			cout << endl << "ERROR. A IS SINGULAR";	  // Matrix A: YOU ARE NOT ALONE :)
			return -1;	//Unhappy return.
		}
		
	/**************************************************************************
	*	PART 3 - Section b : Elimination 								      *
		Have you noticed that the first leg is still looping? :)
	***************************************************************************/
		float coeff; //This is the coefficent between the diagonal and subpivots.
		for(int i = c + 1; i< n;i++) {
			coeff = -1 * a[i][c] / a[c][c]; // coefficent is determined 
			for(int j = 0; j<n; j++) {
				a[i][j] += a[c][j] * coeff; //and implemented to the subpivots to make them ZEROOO!
			}
			b[i] += b[c] * coeff; // Not to forget b vector, though :)
		}			
}	

	/**************************************************************************
	*	PART 4 - Back-Substition								             *
		Let's finish it!
	***************************************************************************/

	float *x; //Dynamic memory allocation for vector x
	x = new float[n]; 
	float sum; // Sum of the A * x, the linear equations
	for(int i = n-1; i>=0; i--) { // nested for loop to obtain the linear equations
		for(int j = n-1; j>= 0; j--) {		
			sum += a[i][j] * x[j]; // the linear equations from final to first . 
			
		}
		
		x[i] = (b[i] - sum) / a[i][i]; // they are then solved and entries of vector x is found.
		
		sum = 0; // sum is initialized to zero to use it again based on the number of our linear equations.	
	}
	
		
	/**************************************************************************
	*	PART 5 - The results								                  *
	*	Printing the x vector to the console and to a text file.              *
	***************************************************************************/
	
	//Nested for loop to print U to the screeen.
	cout << endl << "Upper-Triangularized U Matrix:" << endl; 
	for(int i = 0; i<n; i++){ 
		for(int j=0; j<n; j++) {
			cout << a[i][j] << "  "; 
		}
		cout << endl; 
	}
	
	//For loop to print y to the screen.
	cout << endl << "Vector y, where U * x = y:" << endl;
	for(int i = 0; i<n; i++){ //For loop to print y to the screen.
		cout << b[i] << endl;
	}
	
	//For loop to print x to the screen.	
	cout << endl << "Vector x, where A * x = b:" << endl;
	for(int i = 0; i<n; i++) {
		cout << x[i] << endl;
	}
	
	//For loop to write the x vector to the text file.
	ofstream xfile ("x.txt"); // Ofstream to operate on the file.
	if(xfile.is_open()) { // Check if the file is opened,
		cout << "\nx.txt file is successfully created on the project folder!" << endl;
		for(int i = 0; i<n; i++){
			xfile << x[i] << endl; // If so, write to the text file, as in cout. 
		}
	}
	else cout << "Unable to open x.txt"; // Printed to console in case of failure.	
	
	

	return 0; // Finished the job !
}
