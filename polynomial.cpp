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

void polynomial::normalizePoly()
{
	double divisor = coef[0];
	coef[0] = 1.0;
	for(int i = 1; i <= order; i++)
	{
		coef[i] /= divisor;
	}
}

void polynomial::printPoly()
{
	if(coef != NULL)
	{
		cout << scientific << setprecision(5);
		cout << "Polynomial:" << endl; 
		for(int i = 0; i <= order; i++)
		{
			cout << " ";
			if(i == 0 && coef[0] >= 0)
			{
			  cout << " ";
			}
			if(i != 0 && coef[i] >= 0)
			{
				cout << "+";
			}
			cout << coef[i] << " x^" << order-i << endl;
		}
		cout << resetiosflags(ios::showbase);
	}
}

void polynomial::deletePoly()
{
	delete [] coef;
}
