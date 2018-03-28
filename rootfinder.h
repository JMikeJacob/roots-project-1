#include <complex>

using namespace std;

class rootfinder
{
	private:
		int power;
		bool precision_flag;
		double* factors;
		double* quotient;
		complex<double>* roots;
	public:
		void setup_finder(int order, double* poly);
		void bairstow(int n);
		void quadratic(complex<double>* roots);
		void printRoots();
		void horner(double* poly, int order);
};
