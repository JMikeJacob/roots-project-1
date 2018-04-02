#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <complex>
#include <cmath>
#include "rootfinder.h"
#include "polynomial.h"

double absv(double); //absolute value function
void printDouble(std::ostream&, double, int); 
void saveToFile(std::string, polynomial, rootfinder);
//prints doubles w/ specified sigfigs
#endif
