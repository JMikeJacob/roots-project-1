#include <iostream>
#include <iomanip>
#include <complex>
#include "polynomial.h"
#include "rootfinder.h"
#include <stdlib.h>

using namespace std;

#define MAX_ORDER 20

double absol(double num)
{
  return num * ((num>0) - (num<0));
}

void rootfinder::setup_finder(int order, double* poly)
{
	power = order;
	factors = new double[order+1];
	for(int i = 0; i < order+1; i++)
	{
		factors[i] = poly[i];
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
				if ((iter % 200) == 0) {
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
	
	for(int i = 0; i < n-1; i++)
	{ 
		factors[i] = b[i];
	}
	factors[n] = s;
	factors[n-1] = r;
	
	delete [] b;
	delete [] c;
}



int main(int argc, char** argv) 
{
	polynomial Poly;
	rootfinder Groot;
	
	double array[4] = {1,3,3,1};
	Poly.createPoly(3, array);
	Poly.printPoly();
	Groot.setup_finder(3, Poly.coef);
	cout <<  endl;
	int n = Poly.order;
	while(n > 2)
	{
		Groot.bairstow(n);
		n -= 2;
	}
	Groot.printRoots();
	Poly.deletePoly();
	
	return 0;
}
