#include <iostream>
#include <complex>
#include <cmath>
#include "rootfinder.h"
#ifndef POLYFINDER_H
#define POLYFINDER_H

using namespace std;

class polynomial
{
	public:
		int order;//highest power
		double* coef;//stores coefficients from a_n to a_0 in that order
		void createPoly(int n, double* inputArr);
		void printPoly();
		void deletePoly();
		void normalizePoly();
};

#endif
