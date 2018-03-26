#include <iostream>
#include <complex>
#include <array>
#include <iomanip>
using namespace std;

double horners(double poly[], complex<double> roots[], int order)
{
    int n = order;
    complex<double> result;
    for(int j=0; j<order; j++){
        result = poly[n];
        for (int i=n-1; i>=0; --i){
            result = result*roots[j] + poly[i];
        }
        std::cout.precision(5);
        std::cout << std::scientific<< "f" << roots[j]<< " = " << result << endl;
    }

}