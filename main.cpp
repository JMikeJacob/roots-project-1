#include <iostream>
#include <fstream>
#include <string>
#include "polynomial.h"
#include "rootfinder.h"
#include "misc_functions.h"
#include <cstring>

using namespace std;

#define MAX_ORDER 20

using namespace std;

bool g_fileExists = true;//global var for existence of text file

void getpoly(string fileName, polynomial& Poly)
{
  ifstream polyFile;
  int order = 0;
  polyFile.open(fileName.c_str());
  if(polyFile.fail())
  {//tells the program to exit if file not found
    cout << "Error opening file!";
    g_fileExists = false;
    return;
  }
  cout << endl;
  polyFile >> order;//inserts first number (nth order) to int order
  double* polyArray = new double[order + 1];//stores coefs tmp.
  for(int i = 0; i <= order; i++)
  {//inserts consecutive coefs into the array until the nth coef
      polyFile >> polyArray[i];
  }
  Poly.createPoly(order, polyArray);//creates polynomial to be used
  Poly.printPoly();//prints out polynomial
  delete [] polyArray;//deallocates memory of dynamic array
  polyFile.close();
}
void doubleToFile (string fileName, polynomial Poly, rootfinder Groot)
  {
	fileName = fileName + ".txt";
	char * cfileName = new char [fileName.length()+1];
  	strcpy (cfileName, fileName.c_str());
  	
  	int set;
  	cout << "How many significant figures?" << endl;
  	cin >> set;
  	
	ofstream textFile;
	
	textFile.open(cfileName);
	
	for(int i = 0; i <= Poly.order; i++)
 	{
		printDouble(textFile, Poly.coef[i], set);
		textFile << endl;
	}
	textFile << endl;
	
	for(int i = 0; i < Groot.power ; i++)
	{
	  textFile << "  (";
	  printDouble(textFile, Groot.roots[i].real(), set);
	  textFile << ",";
	  printDouble(textFile, Groot.roots[i].imag(), set);
	  textFile << ")" << endl;
	}
	textFile << endl;
	
	for(int i = 0; i < Groot.power ; i++)
	{
	  textFile << "  (";
	  printDouble(textFile, Groot.evals[i].real(), set);
	  textFile << ",";
	  printDouble(textFile, Groot.evals[i].imag(), set);
	  textFile << ")" << endl;
	}
	textFile << endl;
	
	for(int i=0; i < Groot.power ; i++  )
	{
		textFile << "  f" << "(";
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
	
int main(int argc, char** argv) 
{
  polynomial Poly;
  rootfinder Groot;
  string fileName, save;
  //file reader: user input
  if (argc == 2)
  {//case 1: file name declared along cmd line
    fileName=argv[1];
  }
  else if(argc == 1)
  {//case 2: file name not initially given
    cout<<"Filename:";
    cin >> fileName;
  }
  else
  {//case 3: more than 3 inputs along cmd line
    cout<< "Invalid input. Program name with or w/o file only.";
    return 0;
  }
  if(fileName.find(".txt") == string::npos)
  {//adds file extension if nonexistent
    fileName = fileName + ".txt";
  }
  getpoly(fileName, Poly); //function for extracting from text file
  if(g_fileExists == false)
  {//ends program if file not found
    return 0;
  }
  Poly.normalizePoly();//normalizes polynomial s.t. x^n coef is 1
  Groot.setup_finder(Poly.order, Poly.coef);//sets up dynamic arrays
  cout <<  endl;
  int n = Poly.order;
  while(n > 2)
  {//bairstow algorithm will loop as long as 
   //a quadratic factor can be found
    Groot.bairstow(n);
    n -= 2;
  }
  Groot.extractRoots();//extracts roots from quadratic factors
  Groot.printRoots();
  Groot.horner(Poly.coef, Poly.order);//evaluates roots in polynomial
  //deallocates memory of dynamic arrays
  cout << "Name of save file: " << endl;
  cin >> save;
  doubleToFile(save,Poly,Groot);
  Poly.deletePoly();
  Groot.deleteFinder();
  return 0;
}
