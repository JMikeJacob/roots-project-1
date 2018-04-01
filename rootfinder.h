#include <iostream>
#include <complex>
#include <cmath>
#include <stdlib.h>
#ifndef ROOTFINDER_H
#define ROOTFINDER_H

#define guess 0.0 //defines guess value for r and s

using namespace std;

class rootfinder
{
  private:
    double* factors;//stores factors/quotients
    
  public:
    void setup_finder(int, double*);//sets up necessary values
    void bairstow(int);//main algorithm function
    void quadratic(double,double,complex<double>&,complex<double>&);
    void horner(double*, int);//horner's method
    void extractRoots();
    void printRoots(); 
    void deleteFinder();
    int power;//polynomial order
    complex<double>* roots;//stores roots
    complex<double>* evals;//stores Horner's method results
};

#endif
