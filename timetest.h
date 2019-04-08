#ifndef TINDER
#define TINDER
#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include <ctime>
#include <windows.h>
#include <iomanip>
#include "mingw.thread.h" // std::thread, std::this_thread::sleep_for
#include "mingw.condition_variable.h"
#include "mingw.mutex.h"
#include "mingw.future.h"
#include "mingw.shared_mutex.h"
#include <vector>

using namespace std;

struct dater
{
string name;
int alert; //time that alert is sent
dater *next;
bool safe;

dater(int _time, string _name)
    {
    name = _name;
    alert = _time;
    safe = false;
    }
};

class tinder
{
public:
    tinder(int tableSize);
    ~tinder();
    void addMember(int _time, string name);
    void alertCheck(int currTime);
    void cancelAlert(int index);
    void print();
    int cs();
private:
    //unsigned int getHash(string word);
    int tableSize;
    int currentSize;
    dater **hashTable;
    vector<dater> daters;
    vector<thread> threads;
};

#endif