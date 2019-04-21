#include "ariadneHeader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

User :: User()
{
  string proxy = "EMPTY";
  string initPin = "0000";
  username = userFirstName = userFirstName = proxy;
  pin = initPin;
  EC_firstName = EC_lastName = EC_email = proxy;

  eventsArray = new Event[3];
  for(int i = 0; i < 3; i++){
    eventsArray[i].event = proxy;
    eventsArray[i].timer = -1;
    eventsArray[i].index = -1;
  }
}

User :: ~User()
{
  delete [] eventsArray;
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
string User :: getPin()
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
  this->username = username;
}
void User :: setUser(string firstName, string lastName)
{
  userFirstName = firstName;
  userLastName = lastName;
}
void User :: setPin(string pin)
{
  // Do we add 4 char check here or before passing input to setter?
  this->pin = pin;
}
void User :: setEC_name(string firstName, string lastName)
{
  EC_firstName = firstName;
  EC_lastName = lastName;
}
void User :: setEC_email(string email)
{
  EC_email = email;
}



bool User :: deactivateAlert(string username, int pin)
{

}
void User :: printEvents(string username)
{
  cout << userFirstName << " " << userLastName << "'s Events: " << endl;
  for(int i = 0; i < 3; i++){
    if(eventsArray[i].event != "EMPTY"){
      cout << "Event " << i << ": " << eventsArray[i].event << endl;
      cout << "Time: " << eventsArray[i].timer << " seconds" << endl;
      cout << "Event index: " << eventsArray[i].index << endl;
      cout << endl;
    }
  }
}
void User :: addEvent(string username, string event, int pin)
{
  // I don't think addEvent needs to be passed a username (if we're calling it within the User
  // class we need to already have the user identified) so I think we'll want to call the search from
  // the hash table to return the user and then call addEvent
  // Also how to we want to do prompts? Should all our cout statements be within the driving function
  // or within each function?
}
