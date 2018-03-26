#include <iostream>
#include <complex>
#include <array>
#include <iomanip>
using namespace std;

double horners(complex<double> poly[], complex<double> roots[], int order){
    complex<double> result;
    for(int j = 0; j < order; j++){
        result = poly[order];
        for (int i = order-1; i >= 0; --i){
            result = result*roots[j] + poly[i];
        }
        std::cout.precision(5);
        std::cout << std::scientific<< "f" << roots[j] << " = " << result << endl;
    }

}
