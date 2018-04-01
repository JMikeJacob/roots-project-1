#include "rootfinder.h"
#include "misc_functions.h"

using namespace std;

void rootfinder::setup_finder(int order, double* poly)
{
	power = order;
	factors = new double[order+1];
	roots = new complex<double>[order];
	evals = new complex<double>[order];
	for(int i = 0; i < order+1; i++)
	{
		factors[i] = poly[i];
		if(i < order)
		{
			roots[i] = complex<double>(0.0, 0.0);
			evals[i] = complex<double>(0.0, 0.0);
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
	
	while(absv(dr) + absv(ds) > epsilon)
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
		
		if(absv(d) < 1e-16)
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
	{ //quotient
		factors[i] = b[i];
	}
	//x^2 + rx + s
	factors[n] = s;
	factors[n-1] = r;

	delete [] b;
	delete [] c;
}

void rootfinder::quadratic(double b, double c, complex<double>& root1, 
                           complex<double>& root2)
{
	double epsilon = 1e-6;
	double disc = b*b - 4.0*c;
	if (absv(disc) < epsilon)
	{
		root1 = complex<double>(-b/2.0, 0.0);
		root2 = complex<double>(-b/2.0, 0.0);
		return;
	}
	
	if (disc > 0)
	{
		root1 = complex<double>((-b + sqrt(disc))/2.0, 0.0);
		root2 = complex<double>((-b - sqrt(disc))/2.0, 0.0);
		return;
	}
	
	if (disc < 0)
	{
		root1 = complex<double>(-b/2.0,  sqrt(-disc)/2.0);
		root2 = complex<double>(-b/2.0, -sqrt(-disc)/2.0);
		return;
	}
}

void rootfinder::extractRoots()
{
	for(int i = power; i >= 2; i-=2)
	{
	  quadratic(factors[i-1], factors[i], roots[i-1], roots[i-2]);
	}
	if(power % 2 == 1)
	{
		roots[0] = -factors[1];
	}
}

void rootfinder::horner(double* poly, int order)
{
    complex<double> result;
    double eps = 1e-9;
    cout << " Evaluating polynomial at identified roots:" << endl;
    for(int j = 0; j < order; j++)
    {
        result = complex<double>(poly[0], 0.0);
        for (int i = 1; i <= order; ++i)
        {
            result = result*roots[j] + complex<double>(poly[i], 0.0);
        }
        if(absv(result.real()) < eps && absv(result.imag()) < eps)
        {
        	result = complex<double>(0.0, 0.0);
				}
				else if(absv(result.real()) < eps)
				{
				  result = complex<double>(0.0, result.imag());
				}
				else if(absv(result.imag()) < eps)
				{
					result = complex<double>(result.real(), 0.0);
				}
        cout << "  f" << "(";
				printDouble(roots[j].real(), 5);
				cout << ",";
				printDouble(roots[j].imag(), 5);
				cout << ") = (";
				printDouble(result.real(), 5);
				cout << ",";
				printDouble(result.imag(), 5);
        cout << ")" << endl;
        
        evals[j] = result;
    }
}

void rootfinder::printRoots()
{
	cout << " Roots: " << endl;
	for(int i = 0; i < power; i++)
	{
		cout << "  (";
		printDouble(roots[i].real(), 5);
		cout << ",";
		printDouble(roots[i].imag(), 5);
		cout << ")" << endl;
	}
	cout << endl;
}
