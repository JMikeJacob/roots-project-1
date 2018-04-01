#include "misc_functions.h"

using namespace std;

double absv(double num)
{
  return num * ((num>0) - (num<0));
}

void printDouble(double num, int set)
{
	if(num == 0.0)
	{
		cout << fixed << setprecision(set);
		cout << num;
		return;
	}
	double log_10 = log10(absv(num));
	int digits = trunc(log_10);
	if(log_10 >= 0 && digits <= 5)
	{
		cout << fixed << setprecision(set - digits);
	}
	else if(log_10 < 0 && digits >= -2)
	{
		if(log_10 < trunc(log_10))
		{
			digits -= 1;
		}
		cout << fixed << setprecision(set - digits);
	}
	else
	{
		cout << scientific << setprecision(set);
	}
	cout << num;
	return;
}

