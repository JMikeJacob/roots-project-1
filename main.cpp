#include <iostream>
#include <iomanip>
#include <complex>
#include "polynomial.h"
#include "rootfinder.h"
#include <stdlib.h> //will find a way for rng soon
#include <fstream>
#include <string>

using namespace std;

#define MAX_ORDER 20

using namespace std;

bool g_fileExists = true;

void getpoly(string fileName, polynomial& Poly)
{
  ifstream polyFile;
	int order = 0;
  polyFile.open(fileName.c_str());
  if(polyFile.fail())
  {
    cout << "Error opening file!";
    g_fileExists = false;
    return;
  }
  polyFile >> order;
	double* polyArray = new double[order + 1];
  for(int i = 0; i <= order; i++)
  {
      polyFile >> polyArray[i];
  }
  Poly.createPoly(order, polyArray);
  Poly.printPoly();
  delete [] polyArray;
  polyFile.close();
}

int main(int argc, char** argv) 
{
  polynomial Poly;
  rootfinder Groot;
  string fileName;
  //file reader: user input
  if (argc == 2)
  {
    fileName=argv[1];
  }
  else if(argc == 1)
  {
    cout<<"Filename:";
    cin >> fileName;
  }
  else
  {
    cout<< "Invalid input. Program name with or w/o file only.";
    return 0;
  }
  if(fileName.find(".txt") == string::npos)
  {
    fileName = fileName + ".txt";
  }
  getpoly(fileName, Poly);
  if(g_fileExists == false)
  {
    return 0;
  }
  Poly.normalizePoly();
  Groot.setup_finder(Poly.order, Poly.coef);
  cout <<  endl;
  int n = Poly.order;
  while(n > 2)
  {
    Groot.bairstow(n);
    n -= 2;
  }
  Groot.printRoots();
  Poly.deletePoly();
  return 0;
}
