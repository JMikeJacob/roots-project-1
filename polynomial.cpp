#include "polynomial.h"

using namespace std;

void polynomial::createPoly(int n, double* inputArr)
{
	order = n;
	coef = new double[n+1];
	for(int i = 0; i <= n; i++)
	{
		coef[i] = inputArr[n-i];
	}
}

void polynomial::printPoly()
{
	if(coef != NULL)
	{
		for(int i = order; i >= 0; i--)
		{
			cout << coef[i] << "x^" << 	i << endl;
		}	
	}
}

void polynomial::deletePoly()
{
	delete [] coef;
}
