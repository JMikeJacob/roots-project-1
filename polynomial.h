#include <iostream>
#include <complex>
#include <iomanip>
#include <cmath>
using namespace std;

class polynomial
{
	public:
		int order;
		double* coef;
		void createPoly(int n, double* inputArr);
		void printPoly();
		void deletePoly();
		void normalizePoly();
};
