#include "polynomial.h"
#include "misc_functions.h"

using namespace std;

void polynomial::createPoly(int n, double* inputArr)
{//function for creating a polynomial
	order = n;
	coef = new double[n+1];//allocates memory for coef array
	//as the written algorithm was devised with 
	//a[i] having the coef a_(n-i), n = order e.g. a[0] = a_n
	//the array from the file is inserted in reverse
	for(int i = 0; i <= n; i++)
	{
		coef[i] = inputArr[n-i];
	}
}

void polynomial::normalizePoly()
{//normalizes polynomial such that a_n is 1.0
	double divisor = coef[0];
	coef[0] = 1.0;
	for(int i = 1; i <= order; i++)
	{//divides the rest of the polynomial by a_n
		coef[i] /= divisor;
	}
}

void polynomial::printPoly()
{//function for printing polynomial
	if(coef != NULL)//if polynomial is not empty
	{
		cout << " Polynomial:" << endl; 
		for(int i = 0; i <= order; i++)
		{
			cout << "  ";
			printDouble(coef[i], 5);//prints coef w/ 6 sigfigs
			cout << " x^" << order-i << endl;
		}
	}
}

void polynomial::deletePoly()
{//deallocates memory occupied by coef array
	delete [] coef;
}
