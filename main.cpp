#include <iostream>
#include <iomanip>
#include <complex>
#include "polynomial.h"
#include "rootfinder.h"
#include "math.cpp"
#include <stdlib.h> //will find a way for rng soon

using namespace std;

#define MAX_ORDER 20

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
