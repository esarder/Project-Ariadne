#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include "timetest.h"
#include "mingw.thread.h" // std::thread, std::this_thread::sleep_for
#include <sstream>
#include <fstream>
#include <math.h>
#include <cstdlib>
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
/  d = user struct
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
        string compile = "a";
        string firstName = d->name;
        string lastName = "m";
        string email = "jd@colorado.edu";
        string s1 = compile+" "+firstName+" "+lastName+" "+email;

        system("g++ email2nd.cpp"); //finds and compiles file
        system(s1.c_str());//runs file with string variables

        return;
        }
    else
        {
        cout << d->name << " is safe" << endl;
        return;
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
    
void tinder::addToHash(dater* d)
    {
    int index = hash_func(d->name);

    if(hashTable[index] == NULL)
        {
        hashTable[index] = d;
        }
    else
        {
        dater* curr = hashTable[index];
        while(curr != NULL)
            {
            if(curr->next == NULL)
                {
                curr->next = d;
                break;
                }
            else
                {
                curr = curr->next;
                }
            }
        }
    }

dater* tinder::addMember(int _time, string name)
    {
    dater* newDater = new dater(_time, name);
    thread(pause_thread, newDater->alert, name, newDater).detach();

    cout << newDater->name << endl;
    return newDater;

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
    cout << "index: " << index << endl;
    
    dater* temp = hashTable[index];

    while(temp != NULL)
        {
        if(temp->name == name)
            {
            return temp;
            }
        temp = temp->next;
        }

    temp = hashTable[index-1];
    while(temp != NULL)
        {
        if(temp->name == name)
            {
            return temp;
            }
        temp = temp->next;
        }
    }
/////////VECTOR???????????????

//     void pause_thread(int n, string name, vector<dater> &d, int &index)
// /* n = how many seconds until the timer expires
// /  name = the name of the user
// /  &d = reference to vector of users in the class vector
// /  index = the index of the user in the vector at the time they were inserted
// */
// //void pause_thread(int n, string name, int &size) 
//     {
//     this_thread::sleep_for (chrono::seconds(n));
//     cout << endl;
//     cout << name << "'s alert of " << n << " seconds has ended" << endl;

//     //delete vector index for specified user
//     int position; // users actual position in the vector since users were added or removed
//     for(int i = 0; i < index; i++)
//         {
//         if(d[i].name == name)
//             {
//             position = i;
//             if(d[i].safe == false)
//                 {
//                 cout << d[i].name << " did not check in" << endl;
//                 }
//             else
//                 {
//                 cout << d[i].name << " has checked in" << endl;
//                 }
            
//             }
//         }
//     if(index == 1)
//         {
//         d.erase(d.begin());
//         }
//     else
//         {
//         d.erase(d.begin() + position);
//         }
    
//     }

// tinder::tinder(int size)
//     {
//     tableSize = size;
//     currentSize = 0;
//     }

// tinder::~tinder()
//     {
    
//     }

// void tinder::addMember(int _time, string name)
//     {
//     //dater newDater = new dater(_time, name);
//     dater newDater = dater(_time, name);

//     daters.push_back(newDater);
//     currentSize = daters.size();

//     thread (pause_thread,newDater.alert, name, ref(daters), ref(currentSize)).detach();
//     print();
//     }
