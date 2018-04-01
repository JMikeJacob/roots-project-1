#include "rootfinder.h"
#include <iomanip>
#include <iostream>
#include <complex>
#include <stdlib.h>

using namespace std;

double absol(double num)
{
  return num * ((num>0) - (num<0));
}

void rootfinder::setup_finder(int order, double* poly)
{
	power = order;
	factors = new double[order+1];
	roots = new complex<double>[order];
	for(int i = 0; i < order+1; i++)
	{
		factors[i] = poly[i];
		if(i < order)
		{
			roots[i] = complex<double>(0.0, 0.0);
		}
	}
}

void rootfinder::bairstow(int n)
{
	precision_flag = false;
	int iter = 1;
	double* b = new double[power+1];
	double* c = new double[power+1];
	double r = 0, s = 0, d = 0, dr = 1.0, ds = 0;
	double epsilon = 1e-14;
	
	b[0] = c[0] = 1;
	
	while(absol(dr) + absol(ds) > epsilon)
	{
		if ((iter % 200) == 0)
		{
			r=(double)rand()/16000.;
		}
		if(iter % 500 == 0)
		{
			epsilon *= 10.0;
			precision_flag=1;
			cout << "Loss of precision" << endl;
		}
		b[1] = factors[1] - r;
		c[1] = b[1] - r;
		//high to low
		for(int i = 2; i <= n; i++)
		{
			b[i] = factors[i] - r*b[i-1] - s*b[i-2];
			c[i] = b[i] - r*c[i-1] - s*c[i-2];
		}
		//partial derivatives
		d = c[n-1] * c[n-3] - c[n-2] * c[n-2];
		dr = b[n] * c[n-3] - b[n-1] * c[n-2];
		ds = b[n-1] * c[n-1] - b[n] * c[n-2];
		
		if(absol(d) < 1e-16)
		{
			d = 1.0;
			dr = 1.0;
			ds = 1.0;
		}
		
		dr = dr/d;
		ds = ds/d;
		
		r += dr;
		s += ds;
		iter++;
	}
	cout << n << " : ";
	for(int i = 0; i < n-1; i++)
	{ //quotient
		factors[i] = b[i];
		cout << factors[i] << " ";
	}
	cout << endl;
	//x^2 + rx + s
	factors[n] = s;
	factors[n-1] = r;

	delete [] b;
	delete [] c;
}

void rootfinder::extractRoots()
{
	double disc = 0.0;
	double epsilon = 1e-6;
	if(factors[2]*factors[2] - 4.0*factors[3] < epsilon)
	{
		disc = 0.0;
	}
	else
	{
		disc = factors[2]*factors[2] - 4.0*factors[3]; 
	}
		cout << "!!!" << factors[1] << " " << factors[2] <<  " " << factors[3] << endl;
		cout << "??" << (-factors[2] + sqrt(disc))/2.0 << endl;
		for(int i = power; i >= 2; i-=2)
		{
			if(factors[i-1]*factors[i-1] - 4.0*factors[i] < epsilon)
			{
				disc = 0.0;
			}
			else
			{
				disc = factors[i-1]*factors[i-1] - 4.0*factors[i]; 
			}
		roots[i - 1] = complex<double>((-factors[i-1] + sqrt(disc))/2.0,0.0);
		roots[i - 2] = complex<double>((-factors[i-1] - sqrt(disc))/2.0,0.0);
	}
	if(power % 2 == 1)
	{
		roots[0] = -factors[1];
	}
}

void rootfinder::horner(double* poly, int order)
{
    complex<double> result;
    double epsilon = 1e-15;
    for(int j = 0; j < order; j++)
    {
        result = complex<double>(poly[0], 0.0);
        for (int i = 1; i <= order; ++i)
        {
            result = result*roots[j] + complex<double>(poly[i], 0.0);
        }
        cout << "f" << roots[j] << " = " << result << endl;
        cout << resetiosflags(ios_base::showbase);
    }
}

void rootfinder::printRoots()
{
	for(int i = 0; i < power; i++)
	{
		cout << roots[i] << endl;
	}
}
