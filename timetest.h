#ifndef TINDER
#define TINDER
#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include "mingw.thread.h" // std::thread, std::this_thread::sleep_for
#include <sstream>
#include <fstream>
//copy/paste for windows 10 compile--
// g++ -std=c++11 -D _WIN32_WINNT=0x0A00 timetest.cpp driverTT.cpp

using namespace std;


struct dater
{
string name;
int alert; //time that alert is sent
dater *next;
bool safe;
bool active;

dater(int _time, string _name)
    {
    name = _name;
    alert = _time;
    safe = false;
    active = true;
    next = NULL;
    }
};

class tinder
{
public:
    tinder(int tableSize);
    ~tinder();
    void deleteUser(string _name);
    void addToHash(dater* d);
    dater* addMember(int _time, string name);
    dater* searchUser(string name);
    void cancelAlert(string name);
    void print();
    int cs();
private:
    //unsigned int getHash(string word);
    int tableSize;
    dater **hashTable;
};

#endif
