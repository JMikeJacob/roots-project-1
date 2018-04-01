#include "misc_functions.h"

using namespace std;

double absv(double num) //absolute value function
{
	//if num is positive, num is multiplied by 1 - 0
	//if num is negative, num is multiplied by 0 - 1
  return num * ((num>0) - (num<0));
}

void printDouble(ostream& out, double num, int set)//prints doubles based on sigfigs
{//varies iostream flags to print out a double with specified accuracy
	if(num == 0.0)
	{//special case: number is exactly 0
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
	if(log_10 >= 0 && digits <= 5)
	{//if num >= 1, the base exponent is 10^(integer digits - 1)
		out << fixed << setprecision(set - digits); //ex. 123.450 
	}
	else if(log_10 < 0 && digits >= -2)
	{//if num < 1, base exponent is 10^-(number of zeroes from left - 1)
		if(log_10 < trunc(log_10))
		{//log10({num < 1}) always returns base exponent value less than
		 //predicted if not 1.0x10^-n, so a -1 is added to compensate
			digits -= 1;
		}
		out << fixed << setprecision(set - digits); //ex. 0.00500
	}
	else
	{//if integer part has more than 6 digits or decimal part has more
	 //than 3 zeroes from the left, the numbers are rendered in 
	 //scientific notation for easier reading
		out << scientific << setprecision(set);
	}
	out << num;
	return;
}

