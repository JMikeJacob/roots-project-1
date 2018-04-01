#include <iostream>
#include <complex>
#include <cmath>
#include <stdlib.h>

using namespace std;

class rootfinder
{
	private:
		int power;
		bool precision_flag;
		double* factors;
		double* quotient;
		complex<double>* roots;
		complex<double>* evals;
	public:
		void setup_finder(int order, double* poly);
		void bairstow(int n);
		void quadratic(double,double,complex<double>&,complex<double>&);
		void extractRoots();
		void printRoots();
		void horner(double* poly, int order);
};
