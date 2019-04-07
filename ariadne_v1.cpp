#include "ariadne.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

User :: User()
{

}
User :: ~User()
{

}


string User :: getUsername()
{
  return username;
}
string User :: getUserFirstName()
{
  return userFirstName;
}
string User :: getUserLastName()
{
  return userLastName;
}
int User :: getPin()
{
  return pin;
}
string User :: getEC_firstName()
{
  return EC_firstName;
}
string User :: getEC_lastName()
{
  return EC_lastName;
}
string User :: getEC_email()
{
  return EC_email;
}


void User :: setUsername(string username)
{

}
void User :: setUser(string firstName, string lastName)
{

}
void User :: setPin(int pin)
{

}
void User :: setEC_name(string firstName, string lastName)
{

}
void User :: setEC_email(string email)
{

}



bool User :: deactivateAlert(string username, int pin)
{

}
void User :: printEvents(string username)
{

}
void User :: addEvent(string username, string event, int pin)
{

}
