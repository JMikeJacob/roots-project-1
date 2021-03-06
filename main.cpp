#include <iostream>
#include <fstream>
#include <string>
#include "polynomial.h"
#include "rootfinder.h"
#include "misc_functions.h"

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
	
int main(int argc, char** argv) 
{
  polynomial Poly;
  rootfinder Groot;
  string fileName, save;
  //file reader: user input
  if (argc == 2) //case 1: file name declared along cmd line
  {
    fileName=argv[1]; 
  }
  else if(argc == 1) //case 2: file name not initially given
  {
    cout<<"Filename:";
    cin >> fileName;
    cin.clear();
    cin.ignore(256, '\n');
  }
  else //case 3: more than 3 inputs along cmd line
  {
    cout<< "Invalid input. Program name with or w/o file only.";
    return 0;
  }
  if(fileName.find(".txt") == string::npos) //adds file extension
  {
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
  cout << endl;
  //asks if user wants to save results to a text file
  char ans = 0;
  while(1)
  {
    cout << "Do you want to save the results to a text file? (Y/N) ";
    cin.get(ans);
    cin.clear();
    cin.ignore(256, '\n');
	  if(ans == 'Y' || ans == 'y')
	  {
      cout << "Name of save file: ";
      cin >> save;
      cin.clear();
      if(save.find(".txt") == string::npos) //adds file extension
      {
        save = save + ".txt";
      }
      saveToFile(save,Poly,Groot);
      break;
    }
    else if(ans == 'N' || ans == 'n')
    {
    	break;
		}
	}
  //deallocates memory of dynamic arrays
  Poly.deletePoly();
  Groot.deleteFinder();
  return 0;
}
