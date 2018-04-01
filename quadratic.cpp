#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

void quadratic (double b, double c)
{
	double epsilon = 1e-16;
	complex<double> root1, root2, root;
	
	if (fabs((b*b)-(4*c)) < epsilon)
	{
		root = complex<double>(((-b + sqrt(b*b - 4*c))/2),0);
		cout << root << endl;
	}
	
	if (((b*b)-(4*c)) > 0)
	{
		
		root1 = complex<double>(((-b + sqrt(b*b - 4*c))/2),0);
		root2 = complex<double>(((-b - sqrt(b*b - 4*c))/2),0);
		
		cout << root1 << endl;
		cout << root2 << endl;
	}
	
	if (((b*b)-(4*c)) < 0)
	{
		
		root1 = complex<double>(-b/2,(sqrt(-(b*b - 4*c)))/2);
		root2 = complex<double>(-b/2,(-sqrt(-(b*b - 4*c)))/2);
		
		cout << root1 << endl;
		cout << root2 << endl;
	}
}
