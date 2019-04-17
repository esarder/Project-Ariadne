#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include "timetest.h"
#include "mingw.thread.h" // std::thread, std::this_thread::sleep_for
#include <sstream>
#include <fstream>
#include <math.h>

//copy/paste for windows 10 compile--
// g++ -std=c++11 -D _WIN32_WINNT=0x0A00 timetest.cpp driverTT.cpp

using namespace std;


int hash_func(string username)
    {
    int hash = 0;
    for(int i=0; i<username.length(); i++)
        {
        hash = hash + username[i]*pow(7, i);
        }
    hash = ((hash*23)+(7*username[4]))%10;
    if (hash<0) return (-1)*hash;
    return hash;
    }

/* n = how many seconds until the timer expires
/  name = the name of the user
/  &d = reference to vector of users in the class vector
/  index = the index of the user in the vector at the time they were inserted
*/

void pause_thread(int n, string name , dater* d)
    {
    this_thread::sleep_for (chrono::seconds(n));
    cout << endl;
    cout << d->name << "'s alert of " << n << " seconds has ended" << endl;
    d->active = false;

    if(d->safe == false) //send out email
        {
        cout << "send email" << endl;
        }
    else
        {
        cout << d->name << " is safe" << endl;
        }
    
    }

tinder::tinder(int size)
    {
    tableSize = size;
    hashTable = new dater *[tableSize];
    for(int i = 0; i < size; i++)
        {
        hashTable[i] = NULL;
        }
    }

tinder::~tinder()
    {
    
    }

void tinder::addMember(int _time, string name)
    {
    dater* newDater = new dater(_time, name);

    int index = hash_func(name);

    if(hashTable[index] == NULL)
        {
        hashTable[index] = newDater;
        thread(pause_thread, newDater->alert, name, newDater).detach();
        }
    else
        {
        dater* curr = hashTable[index];
        while(curr != NULL)
            {
            if(curr->next == NULL)
                {
                curr->next = newDater;
                thread(pause_thread, newDater->alert, name, newDater).detach();
                break;
                }
            else
                {
                curr = curr->next;
                }
            }
        }
    }

void tinder::activeCheck()
    {
    dater* curr;
    for(int i = 0; i < 10; i++)
        {
        curr = hashTable[i];
        while(curr != NULL)
            {
            if(curr->active == false)
                {
                cout << "--- " << curr->name << endl;
                }
            curr = curr->next;
            }
        cout << endl;
        }
    }

void tinder::cancelAlert(string name)
    {
    searchUser(name)->safe = true;
    }

void tinder::print()
    {
    cout << "Current Daters" << endl;

    dater* curr;
    for(int i = 0; i < 10; i++)
        {
        curr = hashTable[i];
        while(curr != NULL)
            {
            cout << "--- " << curr->name << " ---> ";
            curr = curr->next;
            }
        cout << endl;
        }
    }

int tinder::cs()
    {
    int count = 0;
    dater* curr;
    for(int i = 0; i < 10; i++)
        {
        curr = hashTable[i];
        while(curr != NULL)
            {
            count++;
            curr = curr->next;
            }
        }
    return count;
    }

dater* tinder::searchUser(string name)
    {
    int index = hash_func(name);
    dater* temp = hashTable[index];

    while(temp != NULL)
        {
        if(temp->name == name)
            {
            return temp;
            }
        temp = temp->next;
        }
    }
