#include <iostream>
#include <iomanip>
#include <complex>
#include "polynomial.h"
#include "rootfinder.h"
#include "math.cpp"
#include <stdlib.h> //will find a way for rng soon
#include <fstream>
#include <string>

using namespace std;

#define MAX_ORDER 20

using namespace std;
void getpoly(string fileName)
{
  ifstream polyFile;
  int order;
  polyFile.open(fileName.c_str());
  if(polyFile.fail())
  {
    cout << "Error opening file!";
    return;
  }
  polyFile>> order;
  double polyArray[order-1];
  for(int i=0; i <= order-1; i++)
  {
      polyFile>> polyArray[i];
      cout<< polyArray[i] << endl;
  }
  polyFile.close();
}

int main(int argc, char** argv) 
{
	polynomial Poly;
	rootfinder Groot;
	string fileName;
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
    if (argc==2)
    {
        fileName=argv[1];
    }
    else if(argc==1)
    {
        cout<<"Filename:";
        cin>> fileName;
    }
    else
    {
        cout<< "Invalid input. Please only enter the program name along with the file you want to be read.\n e.g. polyroot fileName.txt";
        return 0;
    }
    if(fileName.find(".txt") == string::npos)
    {
        fileName = fileName + ".txt";
    }
    getpoly(fileName);
	
	return 0;
}
