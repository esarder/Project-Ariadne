#include "User.h"
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
  eventCount = 0;

  eventsArray = new Event[3];
  for(int i = 0; i < 3; i++){
    eventsArray[i].event = proxy;
    eventsArray[i].timer = -1;
    eventsArray[i].index = -1;
  }
}

User :: User(string username, string userFirstName, string userLastName,
  string pin, string EC_email, string EC_firstName, string EC_lastName)
{
  this->username = username;
  this->userFirstName = userFirstName;
  this->userLastName = userLastName;
  this->pin = pin;
  this->EC_email = EC_email;
  this->EC_firstName = EC_firstName;
  this->EC_lastName = EC_lastName;
  this->eventCount = 0;
  this->safe = true;
  this->
  eventsArray = new Event[3];
  for(int i = 0; i < 3; i++){
    eventsArray[i].event = "proxy";
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

bool User :: setPin(string pin)
{
  if(pin.length()!=4){
    cout << "PIN is not the correct size. Please enter a four digit PIN.\n";
    return false;
  }
  for(int i=0; i<pin.length(); i++){
    if(!(pin[i] >= 48 && pin[i] <= 57)) return false;
  }
  this->pin = pin;
  return true;
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

bool User :: deactivateAlert(string pin)
{
  return true;
}

void User :: printEvents()
{
  if(eventCount!=0){
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
}

void User :: addEvent(string event, string pin)
{
  // I don't think addEvent needs to be passed a username (if we're calling it within the User
  // class we need to already have the user identified) so I think we'll want to call the search from
  // the hash table to return the user and then call addEvent
  // Also how to we want to do prompts? Should all our cout statements be within the driving function
  // or within each function?
}
