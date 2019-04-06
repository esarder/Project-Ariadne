#pragma once
#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>

using namespace std;

struct Event
{
  string event;
  int timer
  int index
};

class User
{
  private:
    string username;
    string userFirstName;
    string userLastName
    int pin;
    string EC_email;
    string EC_firstName;
    string EC_lastName;
    Event* eventsArray[3];

  public:
    string getUserName();
    string getEC_name();
    int getPin();
    string getEC_email();
    string getEC_Name();

    void setUserName(string firstName, string lastName);
    void setEC_name(string firstName, string lastName);
    void setPin(int pin);
    void setEC_email(string email);

    bool deactivateAlert(string username, int pin);
    void printEvents(string username);
    void addEvent(string username, string event, int pin);
};
