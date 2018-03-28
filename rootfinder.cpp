#include "rootfinder.h"
#include <iomanip>
#include <iostream>
#include <complex>

using namespace std;

void rootfinder::horner(double* poly, int order)
{
    complex<double> result;
    for(int j = 0; j < order; j++)
    {
        result = poly[order];
        for (int i = order-1; i >= 0; --i)
        {
            result = result*roots[j] + poly[i];
        }
        cout << setprecision(5) << scientific;
        cout << "f" << roots[j] << " = " << result << endl;
    }
}

void rootfinder::printRoots()
{
	for(int i = power; i >= 2; i-= 2)
	{
		cout << "x^2 + " << factors[i-1] << "x + " << factors[i] << endl;
	}
	if(power%2 == 1)
	{
		cout << "x + " << factors[1]; 
	}
}
