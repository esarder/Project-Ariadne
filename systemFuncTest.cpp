#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main()
{
  string compile = "./a.out";
  string firstName = "John";
  string lastName = "Doe";
  string email = "jd@colorado.edu";
  string s1 = compile+" "+firstName+" "+lastName+" "+email;

  system("g++ systemFuncTest2.cpp"); //finds and compiles file
  system(s1.c_str());//runs file with string variables

  return 0;



}
