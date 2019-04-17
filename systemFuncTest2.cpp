#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
  string firstName = argv[1];
  string lastName = argv[2];
  string email = argv[3];
  cout << endl;
  cout << "Info displayed from test2.cpp" << endl;
  cout << "First Name: " << firstName << endl;
  cout << "Last Name: "  << lastName << endl;
  cout << "E-Mail: " << email << endl;
  cout << endl;

  return 0;
}
