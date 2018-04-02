#include "rootfinder.h"
#include "misc_functions.h"

using namespace std;

void rootfinder::setup_finder(int order, double* poly)
{//sets up values necessary for bairstow's algorithm
  power = order;
  factors = new double[order+1];//stores the factors of the polynomial
  roots = new complex<double>[order];//stores roots
  evals = new complex<double>[order];//stores results from horner's method
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

void rootfinder::bairstow(int n)//main bairstow's algorithm
{
  //a quadratic factor x^2 + rx + s will be determined via
  //synthetic division. the algorithm estimates r and s.
  //if the remainder is approx. zero, x^2 + rx + s is stored
  //as a factor. otherwise, r and s is adjusted by dr/d and ds/d.
  //dr/d and ds/d are determined via a Taylor-series expansion
  //w/ partial derivatives. These can be obtained via synthetic div.
  //dr/d and ds/d are then added to r and s. if the errors dr and ds
  //are greater than epsilon, the algorithm iterates.
  int iter = 1;//counts number of iterations
  double* b = new double[n+1];//stores quotient of first synthdiv
  double* c = new double[n+1];//stores quot of second synthdiv
  double r = guess, s = guess;//guess values initially defined at 0
  double d = 0, dr = 1.0, ds = 0;
  double epsilon = 1e-14;//numbers less than epsilon is treated as 0
  //this algorithm stores coefficients in the manner:
  //b[0]x^n + b[1]x^n-1 +... + b[i]x^n-i
  b[0] = c[0] = 1.0;//ensure than b_n = c_n = a_n = 1.0
  
  while(absv(dr) + absv(ds) > epsilon)
  {//algorithm will continue to iterate as long as
    if ((iter % 200) == 0)
    {//if too many iterations have occurred, it is possible that
     //r and s are too far away from the actual values. thus,
     //r is reassigned a new random guess
      r=(double)rand()/16000.0;
    }
    if(iter % 500 == 0)
    {//if still too many iterations occur after reguessing, 
     //the algorithm signals a loss of precision indicating
     //that the acquired root may be far from the actual.
      epsilon *= 10.0;
    }
    //(n-1)th coefs as shown by Bairstow
    b[1] = factors[1] - r;
    c[1] = b[1] - r;
    //first and second synthetic divisions from highest to lowest coef
    for(int i = 2; i <= n; i++)
    {
      b[i] = factors[i] - r*b[i-1] - s*b[i-2];
      c[i] = b[i] - r*c[i-1] - s*c[i-2];
    }
    //partial derivatives as shown by Bairstow
    d = c[n-1] * c[n-3] - c[n-2] * c[n-2];//denominator
    dr = b[n] * c[n-3] - b[n-1] * c[n-2];//numerator
    ds = b[n-1] * c[n-1] - b[n] * c[n-2];//numerator
  
    if(absv(d) < 1e-16)
    {//if the denominator d becomes too small, dr/d and ds/d becomes
     //too large, necessitating a reset wherein dr/d = ds/d = 1.0
      d = 1.0;
      dr = 1.0;
      ds = 1.0;
		}
    
    dr = dr/d;
    ds = ds/d;
    //adjustments dr and ds are added to r and s
    r += dr;
    s += ds;
    iter++;
  }
  for(int i = 0; i < n-1; i++)
  {//stored as (quotient)*(quadratic factors){*(x - t) if odd power} 
    factors[i] = b[i];
  }
  //x^2 + rx + s
  factors[n] = s;
  factors[n-1] = r;
  //deallocates dynamic array memory
  delete [] b;
  delete [] c;
}

void rootfinder::quadratic(double b, double c, complex<double>& root1, 
                           complex<double>& root2)
{//quadratic formula for extracting roots
  double epsilon = 1e-6;//number less than epsilon is treated as 0
  double disc = b*b - 4.0*c;//discrimant
  //roots are stored in complex<double> variables
  if (absv(disc) < epsilon)
  {//case 1: discriminant = 0, one real root; stored as two
   //to prevent complications especially due to inaccuracy
    root1 = complex<double>(-b/2.0, 0.0);
    root2 = complex<double>(-b/2.0, 0.0);
    return;
  }
	
  if (disc > 0)
  {//case 2: discriminant > 0, two reals roots
    root1 = complex<double>((-b + sqrt(disc))/2.0, 0.0);
    root2 = complex<double>((-b - sqrt(disc))/2.0, 0.0);
    return;
  }
	
  if (disc < 0)
  {//case 3: discriminant < 0, two complex roots
    root1 = complex<double>(-b/2.0,  sqrt(-disc)/2.0);
    root2 = complex<double>(-b/2.0, -sqrt(-disc)/2.0);
    return;
  }
}

void rootfinder::extractRoots()
{//function for extracting roots from factors
  for(int i = power; i >= 2; i-=2)
  {//each quadratic factor can have roots extracted via quad formula
 	  quadratic(factors[i-1], factors[i], roots[i-1], roots[i-2]);
  }
  if(power % 2 == 1)
  {//if a linear factor x - t is present, the root is x = t
    roots[0] = -factors[1];
  }
}

void rootfinder::horner(double* poly, int order)
{//evaluation of polynomials using Horner's method
  complex<double> result;
  double eps = 1e-9;//numbers less than eps are treated as 0
  cout << " Evaluating polynomial at identified roots:" << endl;
  for(int j = 0; j < order; j++)
  {
    result = complex<double>(poly[0], 0.0);
    for (int i = 1; i <= order; ++i)
    {
      result = result*roots[j] + complex<double>(poly[i], 0.0);
    }
    //if either the real or imaginary part, or both, is less than
    //eps, the respective parts are treated as 0
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
    //prints both root and result with specified sigfigs (6S)
    cout << "  f" << "(";
    printDouble(cout, roots[j].real(), 5);
    cout << ",";
    printDouble(cout, roots[j].imag(), 5);
    cout << ") = (";
    printDouble(cout, result.real(), 5);
    cout << ",";
    printDouble(cout, result.imag(), 5);
    cout << ")" << endl;
    
    evals[j] = result;//stores result in array for saving to file
  }
}

void rootfinder::printRoots()
{//function for printing roots
  cout << " Roots: " << endl;
  for(int i = 0; i < power; i++)
  {
    cout << "  (";
    printDouble(cout, roots[i].real(), 5);
    cout << ",";
    printDouble(cout, roots[i].imag(), 5);
    cout << ")" << endl;
  }
  cout << endl;
}

void rootfinder::deleteFinder()
{//deallocates memory for dynamic arrays
  delete [] factors;
  delete [] roots;
  delete [] evals;
}
