


/********************************************
EE 242 Numerical Methods for Electrical Engineering

Project 2: Computing Eigenvalues and Eigenvectors using Normalized 
Power Iteration together with Deflation

*********************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;


/******************************************************
MATRIX CLASS
I created a matrix class to implement matrix operations
******************************************************/ 

class Matrix { 

	/************
	VARIABLES
	************/

	Matrix *x; 			// Declaring x vector to use in power iteration algorithm.
	bool x_isSet; 		// variable to check if x is pre-set, e.g [1, 1, 1].
	Matrix *eigenVec; 	// Eigenvector of the corresponding object.
	int m,n; 			// rows and columns, respectively.
	double dom_eigenv; 	// Dominant eigenvalue of x.
	double **a; 		// Entries of the corresponding object.
	const char* name; 	// Name of the file that possesses the matrix.
	unsigned entry_toBeOned; 	// Normalized entry id of vector x.  
	double TOLERANCE;			// Tolerance value for precision.
	
	public:
		
		
	/************
	CONSTRUCTORS
	************/
	
	//Empty one, used for temporary matrices. 
	Matrix() {};		
	
	//Row-Column pre-determined constructor
	Matrix(int row, int col){ 		
		m = row;
		n = col;
		createMatrix();				//Creates 2D Array based on arguments.
	}
	
	// Constructs matrix from the input file
	Matrix(const char* name) {		
		this->name = name;			//Determines its name.
		setRowsCols();				//Rows and coln quantity is set.
		createMatrix();				//Creates 2D array based on the above func.
		checkIfSquare();			//Checks if row == coln
		fill();						// Fills the entries by the input file.
		
	}
	
	
	
	/******************
	 GETTERS & SETTERS 
	******************/
	
	//A getter to get dominant eigenvalue.
	double getDom_eigenv(){
		return dom_eigenv;
	}
	
	//A getter for the matrix's eigen vector.
	Matrix getEigenVector(){
		return *eigenVec;
	}
	
	
	//Getter returning row number
	float getRow () {						
		return m;
	}
	
	
	
	/*This method returns the coefficent of the corresponding entry, when it would be scaled to the 2nd argument. 
	E.g Assume vector a^(T) = [15, 5, 2, 4], then a.entry_scaleTo(0,3) would yield the coefficent when 0'th element scaled to 3,
	15 / 3 = 5.   
	*/
	double getCoeff(unsigned entry, double to_beScaled = 1){
		if(n = 1) {
			double scalar;
			scalar = a[entry][0] / to_beScaled;
			return scalar;
		}
		else {
			cout << "ERROR: Failed to scale, the argument is not a vector.";
			exit(-1);
		}
	}
	
	
	// Method to set the tolerance.
	void setTolerance(double t) {	
		TOLERANCE = t;
	}
	
	
	//Method to determine row and coln number.
	void setRowsCols(){				
		fstream afile (name);		//To operate on file.
		
		//Garbage input detection.
		if(afile.is_open() != 1) {	
			cerr << "ERROR: File named " << name << " could not opened.";
			exit(1);
		} 
		
		string line;				//String variable to read lines from input file.
		
		/* I have declared cols vector to determine garbage input. Each entry of
			the vector contains the total entries at one single row.
		*/
		vector <int> cols;			//Initialization of the column vector.
		int row = 0;				
		while(getline(afile, line)) {		//Reading lines with getline func.
			cols.push_back(0);				//with every line, a new index is appended.  
			for(int i = 1; i < line.size(); i++) { //For loop to detect spaces between entries.
				if(line.at(i-1) == ' ') {			// If it detects spaces,
					cols.at(row)++;					// Then the column number at that corresponding line will increment.
				}
			}
			cols.at(row)++;							//After the for loop, I incremented one more since column number = 1 + spaces.
			row++;									//row variable is incremented within iteration of every line.
		}
		
		afile.close();								//Closing file after operation.
		
		for(int i = 1; i < cols.size(); i++) {		//For loop to circulate through the vector which contains the number of entries in each line.
			if(cols.at(i-1) != cols.at(i)) {		//If it detects any mismatch, prints the error and quits.
				cerr << "ERROR: Columns of matrix in " << name <<  " are not of same length.";
				exit(-1);
			}
		}
		
		m = row;									// In the end of the operation, class private variables become rows and colns. 
		n = cols.at(0);								// If the computer reads this line, it means all the entries are of same length so choosing any valid index would be fine.
		
	}
	
	//This method creates and arranges the candidate x vector to use in normalized iteration. 
	void set_its_x() {
		x = new Matrix;
		*x = Matrix(m,1);
		x->fillAll(1);
		*x  = *this * (*x);
		int largest = 0;
		for(int i = 0; i < m; i++) {
			if(x->a[i][0] > x->a[largest][0] ) {
				largest = i;
			}
		}
		entry_toBeOned = largest;
		x_isSet = 1;
	}




	/**************
	USEFUL METHODS
	**************/

	// Method to check if the given matrix is square 
	void checkIfSquare(){			
		if (m != n) {
			cerr << "ERROR: Matrix in " << name << " is not a square matrix.";
			exit(-1);				//Quits if it detects any errors.
		}
	}
	
	
	//Method to create 2D Array using Dynamic Memory Allocation.
	void createMatrix(){
		a = new double* [m]; 				//Each row has multiple spaces ie.cols.
		for(int i = 0; i < m; i++) {
			a[i] = new double [n];			//Opening these spaces.
		}
	}
	
	
	//Method to fill the matrix from the text file.
	void fill() {
		fstream afile(name);			//File re-opens.
		for(int i = 0; i < m; i++) {	//Nested for loop to circulate through the dynamic matrix.
			for(int j = 0; j < n; j++) {
				afile >> a[i][j];		//Filling the entries with the text file.
			}
		}
		afile.close();					//Closing the file.
	}
	
	
	//Method to fill the matrix by the desired number.
	void fillAll(double num){			
		for(int i = 0; i < m; i++) {			//Nested for loop to circulate through the matrix.
			for(int j = 0; j < n; j++) {
				a[i][j] = num;					//Filling operation.
			}
		}
	}
	
	
	/*Method to fill the diagonals of the matrix with the desired number, zero elsewhere. 
	No argument-call refers to creating an identity matrix.
	*/
	void fillDiagonals(float num = 1) {			
		for(int i = 0; i < m; i++) {			//Nested for loop to circulate the matrix.
			for (int j = 0; j < n; j++) {
				if(i == j) {					//When diagonals are detected,
					a[i][j] = num;				//They are filled with that number.
				}
				else{
					a[i][j] = 0;				//O.w filled with zero.
				}
			}
		}
	}
	
	//A method to display the entries of the Matrix object.
	void display() {
		for(int i = 0; i<m; i++){			//Nested loop to circulate the array.
			for(int j=0; j<n; j++) {
				cout << a[i][j] << "  ";  	//Some indentation.
			}
			cout << endl;					//indentation++;
		}
	}
	
	
	//This method converts 1x1 Matrix to a scalar. Used in deflation.
	double convert2Scalar() {
		double scalar;
		if(m == 1 & n == 1) {
			scalar = a[0][0];
		}
		else{
			cout << "ERROR! Failed to convert. Not a 1x1 Matrix.";
			exit(1);
		}
		return scalar;
	}
	
	
	//This method gets the second norm a vector and throws an error if it detects not a vector. Used in calculating deflation.
	double getSecondNorm () {
		if(n == 1 ) {
			double sum = 0;
			for(int i = 0; i < m; i++ ) {
				sum += a[i][0];
				
			}
			sum = sqrt(sum);
			return sum;	
		}
		else {
			cout << "ERROR! NOT A VECTOR";
		}
	}
	
	
	//This method prints the matrix to the file.
	void printFile (ofstream& outfile) {
		outfile << "Eigenvector #1: " << endl;
		for(int i = 0; i < m; i++) {
				outfile << a[i][0] << endl; 
			}
	}
	
	
	
	
	/***************************************
	 CLASS OPERATIONS
	***************************************/
	
	//Operation * receives a rhs matrix, implements matrix multipication and finally returns the result, throws an error if it detects invalid input. 
	Matrix operator* (const Matrix& rhs) {
		Matrix result(m, rhs.n);
		if( this->n == rhs.m) {
			for(int i = 0; i < this->m; i++) {
				for(int j = 0; j < rhs.n; j++) {
					for(int l = 0; l < n; l++) {
						result.a[i][j] += this->a[i][l] * rhs.a[l][j];
					}
				}
			}
			return result;
		}
		else{
			throw std::invalid_argument("ERROR: Matrix dimensions does not agree");
		}
	}
	
	
	//Operation ~ takes the matrix's transpose and returns it. 
	Matrix operator~ (){
		Matrix transpose(n,m);
		
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				transpose.a[j][i] = a[i][j];
				
			}
		}
		
		return transpose;
	}
	
	
	//Operation ^ scales the matrix and returns the scaled version.
	Matrix operator^(double scalar) {
		Matrix scaledMatrix(m,n);
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				scaledMatrix.a[i][j] = scalar * a[i][j];
			}
		}
		return scaledMatrix;
	}
	
	//Operation - implements matrix subtraction and returns the result, throws an error if it receives invalid input. 
	Matrix operator- (const Matrix& mat) {
		if(mat.m == this->m && mat.n == this->n) {
			Matrix temp(mat.m, mat.n);
			for(int i = 0; i < m; i++) {
				for(int j = 0; j < n; j++) {
					temp.a[i][j] = a[i][j] - mat.a[i][j];
				}
			}
			return temp;
		}
		else{
			throw std::invalid_argument("ERROR: Matrix dimensions does not agree");
		}
	}
	



	/**************************
	NORMALIZED POWER ITERATION
				&
			DEFLATION
	**************************/
	
	//This method removes the dominant eigenthings of the corresponding matrix and returns the removed matrix called B.
	Matrix removeDominants(){
		Matrix temp1, temp2, temp3, temp4, B;		//4 temp matrices for intermediate operations and B matrix are constructed.
		temp1 = ~*eigenVec * *eigenVec;				// temp1 = transpose(eigenVector) * eigenvector, temp1 is a (1x1 matrix) 
		temp2 = *eigenVec * ~*eigenVec;				// temp2 = eigenVector * transpose(eigenvector) (m x n Matrix where m = n)
		temp3 = temp2.operator^(1 / temp1.convert2Scalar());	// Scaling operation : temp3 = temp1 * temp2, where temp1 is a scalar. 
		temp4 = temp3.operator^(dom_eigenv);		// Scaling operation: temp4 = Dominant Eigen Value * temp3.
		B = *this - temp4; 							// Finally, B = A - temp4.
		
		B.TOLERANCE = TOLERANCE;					// A's inheritence is assigned to B.
		B.x_isSet = 0;								//B's x will be set during calculating eigen things.
		return B;	 								
	}

	
	//This method is the heart of the program. It calculates the eigenthings of the matrix with recursion, using normalized power iteration algorithm.
	double calc_eigenThings (){
		if(x_isSet == 0) { set_its_x(); }		//Check if the candidate x is set.
		
		/* Static variables since we don't want them to lose their value in each recursion. */
		static double ratio[2] = {0, 1};	
		static double scalar[4];			//Scalars will be determined
		static int i = 0;
		static int j = 0;
		
		
		*x  = *this * (*x);  	// The candiate is refreshed with A * x in every recursion. Thus, A * A * A * ....... A * x until the condition is met
		scalar[i] = x->getCoeff(entry_toBeOned);	// Scalar is determined via obtaining x's largest entry. 
		
		
		if(i%2 == 1) {	//If scalar pairs are determined,
			ratio[j] = scalar[i] / scalar[i-1];				//Ratio[0] = Scalar[1] - Scalar[0] and Ratio[0] = Scalar[3] - Scalar[2], according to i.
			
			if(abs(ratio[j] - ratio[j-1]) < TOLERANCE) {	//If ratio difference falls behind the tolerance,
				dom_eigenv = ratio[j];						//Then largest ratio will be the dominant eigen value.
				eigenVec = new Matrix;						//Eigen vector is formed.
				*eigenVec = x->operator^(1/scalar[i]);		//Eigen vector is the last x's scaled version.
				return dom_eigenv;							//We get dominant eigenvalue.
			}
			j++; if(j == 2) {j = 0;}			//Ratio will cycle through 1 and 0.
		} 
		
		i++; if(i == 4) {i = 0;}				// Scalars will circulate through 0 to 4
		
		
		return calc_eigenThings();		//If the condition is not met, return yourself :) (*swh)
	}
};



int main(int argc, char** argv) {
	
	/* PARAMETERS TO MAIN */
	const char* input = argv[1];	//First parameter is taken as input.
	const char* output = argv[3];	//Third is output file.
	double tol = atof(argv[2]);		//Second is the tolerance.
	
	
	/* 	INPUT MANIPULATION */
	Matrix A (input); 				/*A new matrix called A is created by the constructor that takes the filename. */
	A.setTolerance(tol);			//Tolerance is set.
	
	A.calc_eigenThings(); 			//The object's eigenthings are found by this method. 
	
	
	/* PRINTING THE EIGENTHINGS TO CONSOLE */
	cout << setprecision(2) << fixed; 								//Floating point output precision is set to 2.
	cout << "Eigenvalue #1: " << A.getDom_eigenv() << endl << endl; 
	cout << "Eigenvector #1: " << endl;
	A.getEigenVector().display();
	
	/* DEFLATION */
	Matrix B = A.removeDominants(); // A's eigenthings are removed to find the matrix B.
	B.calc_eigenThings();			// The same operation to B.


	/* PRINTING THE B'S EIGENVALUE TO CONSOLE */
	cout << endl << "Eigenvalue #2: " << endl << B.getDom_eigenv() << endl << endl;
	
	//cout << "Eigenvector #2: " << endl;	//OPTIONAL
	//B.getEigenVector().display();			//OPTIONAL

	/* OUTPUT FILE MANIPULATION */	
	ofstream outfile (output); 
	
	if(outfile.is_open()) { 
		outfile << setprecision(2) << fixed; 		//Floating point precision is set to 2.
		outfile << "Eigenvalue #1: " << endl << A.getDom_eigenv() << endl << endl;		//A's eigenvalues are written by cout.
		A.getEigenVector().printFile(outfile);		//A method is used since it is a vector.
		outfile << endl << "Eigenvalue #2: " << endl << B.getDom_eigenv();	//B's eigen value is printed.
		cout << endl <<  output << " is successfully created!\n";		//Error detection.
	}
	else cout << "Unable to open x.txt"; 		//Error detection.
	outfile.close();
	
	return 0;
}


