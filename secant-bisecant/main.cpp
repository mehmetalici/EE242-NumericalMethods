
/**************************************************

EE 242 Numerical Methods for Electrical Engineering
Project 3: Secant and Bisection Methods

***************************************************/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


/*****************

Class "Function"	
						   
*****************/
class Function {
	private:
		vector<double> coeffs; // Dynamic Vector to store the coefficents.
		double tol; 		   //Tolerance value
		double x; 			   // the x in f(x).
		vector<double>::iterator it; // iterator to cycle through coeffs vector.
		int count_sec;		   // Iteration count in secant method.
		int count_bisect;	   // Iteration count in bisecant method.
		double x0, x1, x2;	   // Recurring values in secant method.
		double a, b, c;		   // Recurring values in bisection method.
		
		
	public:
		/* Constructor */
		Function(vector<double> c){
			coeffs = c;
		}
		
		/* Method to get the unknown x's value. For example:
		   let x = 3, and we would like to find x^5. Then,
		   getX(3, 5) will return 3^5, which is 243.	 */
		double getX(double x, int order){
			if(order == 0) { // i.e x^0 = 1, for all x.
				return 1;
			}
			double result = 1;
			while(order > 0) {
				result *= x;
				order--;
			}
			return result;
		}
		
		/******************* 
		GETTERS && SETTERS 
		*******************/
		
		/* Secant Method iteration counter getter.  */
		int getCount_sec(){
			return count_sec;
		}
		
		/*1st recurring endpoint in Bisection Method getter. */
		double getA(){
			return a;
		}
		
		/*2nd recurring endpoint in Bisection Method getter. */
		double getB(){
			return b;
		}
		
		/*1st recurring endpoint in Secant Method getter. */
		double getx0(){
			return x0;
		}
		
		/*2nd recurring endpoint in Secant Method getter. */
		double getx1(){
			return x1;
		}
		
		/* Bisection Method iteration counter getter. */
		int getCount_bisect(){
			return count_bisect;
		}
		/* Tolerance setter. */
		setTol(double tol){
			this->tol = tol;
		}		
		
		
		
		/********
		 METHODS
		********/
		
		/* Method to print the actual function for user.
		   let coeffs = [2 3 0 1]. This method will print in:
		   y = 2x^4 + 3x^3 + 3x^2 + 1 	*/
		print() {
			int j = coeffs.size();
			cout << "The function:" << endl <<"y = ";
			for (it = coeffs.begin(); it != coeffs.end(); ++it){
				j--; 
				if(*it == 0) {continue;}
				cout << *it;	
    			if(j == 1) {
					cout << "x" << " +" << ' ';
				}
				else if(j > 0 ) {
    				cout << "x^" << j << " +" << ' '; 
				}
			}
			cout << endl << endl;
		}
		

		
		/* Method to calculate the numeric value of a function. For example:
		   let f1(x) = x^2 + 3x + 5.
		   f1.calc(2) = 2^2 + 3.2 + 5 = 15.								 */
		double calc(double v){
			double result = 0;
			int order = coeffs.size();
			int j = coeffs.size()-1; // Decrementing one since the coefficent array initializes from 0.
			for (int i = 0; i < order; i++){
				result += coeffs.at(i) * getX(v, j);
				j--;
			}
			return result;
		}
		
		// IMPORTANT NOTE: In two methods, I have started the counter at -1. The reason is explained in detail at readme.txt. 
		
		/***************************
		SECANT METHOD IMPLEMENTATION
		****************************/
		/* Recursive method that takes two guesses and optional iterator and returnes the root*/
		double getRootbySec(double x0, double x1, int it = -2){
			
			double x2;
			static int count = 0;
			
			/* Root finding difference relation. */
			x2 = x1 - calc(x1) * (x1 - x0) / (calc(x1) - calc(x0));
			
			/* if optional argument is entered  */
			if(it == count){
				count = 0;
				this->x0 = x0;
				this->x1 = x1;
				return x2;	
			} 
			
			
			/* Endpoint relation is based. If it does not converge, recur! */
			if(abs(x1 - x0) > tol) {
				count++;
				return getRootbySec(x1, x2, it);
			}
			
			/* means converged. Then do the cleaning. */ 
			count_sec = count;
			count = 0;
			this->x0 = x0;
			this->x1 = x1;
			return x2;
		}
		
		
		
		/******************************
		BISECTION METHOD IMPLEMENTATION
		*******************************/
		
		/*
		A quick method to check if the function values of two guesses, i.e a and b
		are of opposite sign. 													*/  
		bool isOppositeSign(double a, double b) {
			if (calc(a) * calc(b) < 0) {
					return true;
				}
		}
		
		/* 
		A recursive method that gets two guesses and an optional iteration value 
		from the main and returns the root. 								    */
		double getRootbyBisect(double a, double b, int it = -2) {
			
			if(isOppositeSign(a, b) == false) {
				cout << "ERROR: The function values are not of opposite sign.";
				exit(-1);				
			}
			static int count = 0; //A static counter since the func is recursive.
		
			double c = (a + b) / 2; // Finding the midpoint. 
		
			/*If default value is given, then recursion will stop at that point.*/
			if(it == count){
				/* Storing recurrence values. We will need them at Hybrid Method.*/
				this->a = a; 
				this->b = b; 
				count_bisect = count; // I decremented the first operation. Since it's not an iteration.
				count = 0; // Count is reset after the operation. 			
				return c; // Root is returned.
			}
			 
			
			/* Recur until the endpoint converges.  */
			if(abs(c-b) > tol) { 	// OPTIONAL: use if(abs(calc(c)) >= tol) for function convergence.
				count++;
				if(isOppositeSign(a, c)) {
					return getRootbyBisect(a, c, it);
				}
				if(isOppositeSign(b, c)) {
					return getRootbyBisect(b, c, it);
				}
			}
			/* If the computer reaches here, it means the func converged.*/
			/* Storing recurrence values and returning with the root. */
			count_bisect = count;
			count = 0;
			this->a = a;
			this->b = b;
			return c;
		}
		
};

int main(int argc, char** argv) {
	
	/*INPUT MANIPULATION */
	double tol = atof(argv[argc-1]);
	double guess1 = atof(argv[argc-3]);
	double guess2 = atof(argv[argc-2]);

	vector<double> coeffs;
	for(int i = 1; i < argc-3; i++) {
		coeffs.push_back(atof(argv[i]));
	}
	
	/* CREATING A CLASS INSTANCE */
	Function f2(coeffs);
	f2.setTol(tol);
	//f2.print(); OPTIONAL
	
	/* SECANT METHOD MANIPULATION */
	cout << "The Secant Method" << endl;	
	cout << "Root: " << f2.getRootbySec(guess1, guess2) << endl;
	cout << "# of Iterations: " << f2.getCount_sec() << endl << endl;
	
	/* BISECTION METHOD MANIPULATION */
	cout << "The Bisection Method" << endl;
	cout << "Root: " << f2.getRootbyBisect(guess1, guess2) << endl;
	cout << "# of Iterations: " << f2.getCount_bisect() << endl << endl ;
	
	
	/* HYBRID METHOD MANIPULATION, */
	int it_bisec = 2; // 2 recursion.
	cout << "A Hybrid Method with a combination of the two" << endl;
	f2.getRootbyBisect(guess1, guess2, it_bisec+1); 
	/* GET THE CANDIDATES AND SEND IT TO SECANT METHOD */
	cout << "Root: " << f2.getRootbySec(f2.getA(), f2.getB()) << endl; 
	cout << "# of Iterations: " << f2.getCount_sec() + it_bisec << endl << endl;
	


	
	return 0;
}
