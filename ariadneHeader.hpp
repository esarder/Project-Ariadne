#pragma once
#ifndef CLASS_HPP
#define CLASS_HPP


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
    Event* eventsArray;

  public:
    User();
    ~User();

    string getUsername();
    string getUserFirstName();
    string getUserLastName();
    string getPin();
    string getEC_firstName();
    string getEC_lastName();
    string getEC_email();

    void setUsername(string username);
    void setUser(string firstName, string lastName);
    void setPin(string pin);
    void setEC_name(string firstName, string lastName);
    void setEC_email(string email);

    bool deactivateAlert(string username, int pin);
    void printEvents(string username);
    void addEvent(string username, string event, int pin);

    User* next;
};

#endif
