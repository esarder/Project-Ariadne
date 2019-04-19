#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <chrono>         // std::chrono::seconds
#include <thread> //FOR MAC
// #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for //FOR PC

#include "User.h"

using namespace std;

void pause_thread(int n, string name , Event currEvent, User currUser){
    this_thread::sleep_for (chrono::seconds(n));
    cout << endl;
    cout << currUser.getUserFirstName() << "'s alert of " << n;
    cout << " seconds for " << currEvent.event << " has ended" << endl;
    currUser.subEventCount();
    if(currUser.getEventCount()==0){
      currUser.setInactive();
      currUser.setSafe();
    }

    if(currUser.getSafe() == false) //send out email
        {
        cout << "send email" << endl;
        string compile = "a";
        string firstName = currUser.getEC_firstName();
        string lastName = currUser.getEC_lastName();
        string email = currUser.getEC_email();
        string s1 = compile+" "+firstName+" "+lastName+" "+email;

        //NEED TO UPDATE SYSTEM STUFF

        // system("g++ email2nd.cpp"); //finds and compiles file
        // system(s1.c_str());//runs file with string variables

        return;
        }
    else
        {
        cout << currUser.getUserFirstName() << " " << currUser.getUserLastName();
        cout << " is safe" << endl;
        return;
        }
}

User :: User(){
  string proxy = "EMPTY";
  string initPin = "0000";
  username = userFirstName = userFirstName = proxy;
  pin = initPin;
  EC_firstName = EC_lastName = EC_email = proxy;
  eventCount = 0;
  this->eventCount = 0;
  this->safe = true;
  this->active = false;

  eventsArray = new Event[3];
  for(int i = 0; i < 3; i++){
    eventsArray[i].event = proxy;
    eventsArray[i].timer = -1;
    eventsArray[i].index = -1;
  }
}

User :: User(string username, string userFirstName, string userLastName,
  string pin, string EC_email, string EC_firstName, string EC_lastName){
  this->username = username;
  this->userFirstName = userFirstName;
  this->userLastName = userLastName;
  this->pin = pin;
  this->EC_email = EC_email;
  this->EC_firstName = EC_firstName;
  this->EC_lastName = EC_lastName;
  this->eventCount = 0;
  this->safe = true;
  this->active = false;

  eventsArray = new Event[3];
  for(int i = 0; i < 3; i++){
    eventsArray[i].event = "EMPTY";
    eventsArray[i].timer = -1;
    eventsArray[i].index = -1;
  }
}

/*
Commented out line throws and arbort 6 error at end of program. Not sure why.
this is the error:
run(2754,0x113b485c0) malloc: *** error for object 0x7ffee376e748: pointer being freed was not allocated
run(2754,0x113b485c0) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6
*/
User :: ~User(){
  // delete [] eventsArray;
}

string User :: getUsername(){
  return username;
}

string User :: getUserFirstName(){
  return userFirstName;
}

string User :: getUserLastName(){
  return userLastName;
}

string User :: getPin(){
  return pin;
}

string User :: getEC_firstName(){
  return EC_firstName;
}

string User :: getEC_lastName(){
  return EC_lastName;
}

string User :: getEC_email(){
  return EC_email;
}

void User :: setUsername(string username){
  this->username = username;
}

void User :: setUser(string firstName, string lastName){
  userFirstName = firstName;
  userLastName = lastName;
}

bool User :: setPin(string pin){
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

void User :: setEC_name(string firstName, string lastName){
  EC_firstName = firstName;
  EC_lastName = lastName;
}

void User :: setEC_email(string email){
  EC_email = email;
}

bool User :: deactivateAlert(string pin){
  return true;
}

void User :: printEvents(){
  if(eventCount!=0){
    cout << userFirstName << " " << userLastName << "'s Events: " << endl;
    for(int i = 0; i < 3; i++){
      if(eventsArray[i].event != "EMPTY"){
        cout << "Event " << i+1 << ": " << eventsArray[i].event << endl;
        cout << "Time: " << eventsArray[i].timer << " seconds" << endl;
        cout << endl;
      }
    }
  }
}

void User :: addEvent(string _event, int _timer){

  if(!(getEventCount() < 4)){
    cout << getUsername() << " has too many events currently! Event not able to";
    cout <<  " add event at this time.";
    return;
  }
  else{
    Event *addEvent = new Event;
    addEvent->event = _event;
    addEvent->timer = _timer;
    addEvent->index = getEventCount();
    eventsArray[getEventCount()] = *addEvent;
    addEventCount();
    setUnsafe();
    setActive();

    thread(pause_thread, _timer, name, ).detach();
    
    }
}

bool User :: addEventCount(){
  if(eventCount<4){
    eventCount++;
    return true;
  }
  return false;
}

bool User :: subEventCount(){
  if(eventCount>0){
    eventCount--;
    return true;
  }
  return false;
}

int User :: getEventCount(){
  return eventCount;
}

void User :: setSafe(){
  safe = true;
}

void User :: setUnsafe(){
  safe = false;
}

bool User :: getSafe(){
  return safe;
}

void User :: setActive(){
  active = true;
}

void User :: setInactive(){
  active = false;
}

bool User :: getActiveStatus(){
  return active;
}
