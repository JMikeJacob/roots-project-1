#include "misc_functions.h"

using namespace std;

double absv(double num) //absolute value function
{
	//if num is positive, num is multiplied by 1 - 0
	//if num is negative, num is multiplied by 0 - 1
  return num * ((num>0) - (num<0));
}

void printDouble(ostream& out, double num, int set)
{//varies iostream flags to print out a double with specified accuracy
 //ostream& allows the function to either print the double (with cout)
 //or save it in the file (with ofstream) depending on what 
 //output stream is passed as the parameter
  if(num == 0.0)
  {
    //special case: number is exactly 0
    if(set > 5 || set < -2)
    {
      out << scientific << setprecision(set);
    }
    else
    {
      out << fixed << setprecision(set);
    }
    out << num;
    return;
  }
  //counts total number of sigfigs based on base expt
  double log_10 = log10(absv(num)); 
  int digits = trunc(log_10); //gets integer part only
  if(log_10 >= 0 && digits <= 5 && set >= digits)
  {
    //if num >= 1, the base exponent is 10^(integer digits - 1)
    out << fixed << setprecision(set - digits); //ex. 123.450 
  }
  else if(log_10 < 0 && digits >= -2 && set <= 5)
  {
    //if num < 1, base exponent is 10^-(number of zeroes from left-1)
    if(log_10 < trunc(log_10))
    {
     //log10({num < 1}) always returns base exponent value less than
     //predicted if not 1.0x10^-n, so a -1 is added to compensate
      digits -= 1;
    }
    out << fixed << setprecision(set - digits); //ex. 0.00500
  }
  else
  {
    //if integer part has more than 6 digits or decimal part has more
    //than 3 zeroes from the left, the numbers are rendered in 
    //scientific notation for easier reading
    out << scientific << setprecision(set);
  }
  out << num;
  return;
}

void saveToFile(string fileName, polynomial Poly, rootfinder Groot)
{
  int set;
  cout << "How many significant figures? ";
  cin >> set;
  cin.clear();
  cin.ignore(256, '\n');
  set = set - 1;	
  ofstream textFile;
	
  textFile.open(fileName.c_str());
	
	textFile << "Polynomial:" << endl;
  for(int i = 0; i <= Poly.order; i++)
  {
  	textFile << " ";
    printDouble(textFile, Poly.coef[i], set);
    textFile << " x^" << Poly.order - i << endl;
  }
  textFile << endl;
	
	textFile << "Roots:" << endl;
  for(int i = 0; i < Groot.power ; i++)
  {
    textFile << " (";
    printDouble(textFile, Groot.roots[i].real(), set);
    textFile << ",";
    printDouble(textFile, Groot.roots[i].imag(), set);
    textFile << ")" << endl;
  }
  textFile << endl;
	
	textFile << "Evaluating polynomial at identified roots:" << endl;
  for(int i=0; i < Groot.power ; i++  )
  {
    textFile << " f" << "(";
    printDouble(textFile, Groot.roots[i].real(), set);
    textFile << ",";
    printDouble(textFile, Groot.roots[i].imag(), set);
     textFile << ") = (";
    printDouble(textFile, Groot.evals[i].real(), set);
	  textFile << ",";
    printDouble(textFile, Groot.evals[i].imag(), set);
    textFile << ")" << endl;
  }
	
  textFile.close();
}

