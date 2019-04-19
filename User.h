#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

struct Event
{
  string event;
  int timer;
  int index;
};

class User
{
  private:
    string username;
    string userFirstName;
    string userLastName;
    string pin;
    string EC_firstName;
    string EC_lastName;
    string EC_email;
    int eventCount;
    Event* eventsArray;
    //from timer
    bool safe;
    bool active;

  public:
    User();
    User(string, string, string, string, string, string, string);
    ~User();

    string getUsername();
    string getUserFirstName();
    string getUserLastName();
    string getPin();
    string getEC_firstName();
    string getEC_lastName();
    string getEC_email();
    bool addEventCount();
    bool subEventCount();

    void setUsername(string username);
    void setUser(string firstName, string lastName);
    bool setPin(string pin);
    void setEC_name(string firstName, string lastName);
    void setEC_email(string email);

    bool deactivateAlert(string pin);
    void printEvents();
    void addEvent(string event, string pin);

    User* next;
};

#endif
