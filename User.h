#include <chrono>         // std::chrono::seconds
#include <thread> //FOR MAC
// #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for //FOR PC
#include <iostream>

#pragma once
#ifndef USER_H
#define USER_H

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
    bool getSafe();
    bool getActiveStatus();
    int getEventCount();

    bool addEventCount();
    bool subEventCount();

    void setSafe();
    void setUnsafe();
    void setActive();
    void setInactive();
    bool deactivateAlert();

    void setUsername(string username);
    void setUser(string firstName, string lastName);
    bool setPin(string pin);
    void setEC_name(string firstName, string lastName);
    void setEC_email(string email);

    void printEvents();
    void addEvent(string event,int timer, User* u);
    bool writeEmail(string, string, string, string, string);

    User* next;
};

#endif

// #include <chrono>         // std::chrono::seconds
// #include <thread> //FOR MAC
// // #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for //FOR PC
// #include <iostream>
//
// #pragma once
// #ifndef USER_H
// #define USER_H
//
// using namespace std;
//
// struct Event
// {
//   string event;
//   int timer;
//   int index;
// };
//
// class User
// {
//   private:
//     string username;
//     string userFirstName;
//     string userLastName;
//     string pin;
//     string EC_firstName;
//     string EC_lastName;
//     string EC_email;
//     int eventCount;
//     Event* eventsArray;
//     //from timer
//     bool safe;
//     bool active;
//
//   public:
//     User();
//     User(string, string, string, string, string, string, string);
//     ~User();
//
//     string getUsername();
//     string getUserFirstName();
//     string getUserLastName();
//     string getPin();
//     string getEC_firstName();
//     string getEC_lastName();
//     string getEC_email();
//     bool addEventCount();
//     bool subEventCount();
//     int getEventCount();
//
//     void setSafe();
//     void setUnsafe(User* u);
//     bool getSafe();
//     void setActive();
//     void setInactive();
//     bool getActiveStatus();
//
//     void setUsername(string username);
//     void setUser(string firstName, string lastName);
//     bool setPin(string pin);
//     void setEC_name(string firstName, string lastName);
//     void setEC_email(string email);
//
//     bool deactivateAlert(string pin);
//     void printEvents();
//     void addEvent(string event,int timer, User* u);
//     bool writeEmail(string, string, string, string, string);
//
//     User* next;
// };
//
// #endif
