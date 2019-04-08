#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include <ctime>
#include <windows.h>
#include <iomanip>
#include "timetest.h"
#include "mingw.thread.h"
#include "mingw.condition_variable.h"
#include "mingw.mutex.h"
#include "mingw.future.h"
#include "mingw.shared_mutex.h"

using namespace std;



void pause_thread(int n, string name, vector<dater> &d, int &index)
/* n = how many seconds until the timer expires
/  name = the name of the user
/  &d = reference to vector of users in the class vector
/  index = the index of the user in the vector at the time they were inserted
*/
//void pause_thread(int n, string name, int &size) 
    {
    this_thread::sleep_for (chrono::seconds(n));
    cout << endl;
    cout << name << "'s alert of " << n << " seconds has ended" << endl;

    //delete vector index for specified user
    int position; // users actual position in the vector since users were added or removed
    for(int i = 0; i < index; i++)
        {
        if(d[i].name == name)
            {
            position = i;
            if(d[i].safe == false)
                {
                cout << d[i].name << " did not check in" << endl;
                }
            else
                {
                cout << d[i].name << " has checked in" << endl;
                }
            
            }
        }
    if(index == 1)
        {
        d.erase(d.begin());
        }
    else
        {
        d.erase(d.begin() + position);
        }
    
    }

tinder::tinder(int size)
    {
    tableSize = size;
    currentSize = 0;
    }

tinder::~tinder()
    {
    
    }

void tinder::addMember(int _time, string name)
    {
    //dater newDater = new dater(_time, name);
    dater newDater = dater(_time, name);

    daters.push_back(newDater);
    currentSize = daters.size();

    thread (pause_thread,newDater.alert, name, ref(daters), ref(currentSize)).detach();
    print();
    }

void tinder::cancelAlert(int index)
    {
    //find thread ID based on name/pin argument
    //pass exitSignal.set_value() to said thread ID
    daters[index].safe = true;
    }
void tinder::print()
    {
    cout << "Current Daters" << endl;
    for(int i = 0; i < daters.size(); i++)
        {
        cout << "--- " << daters[i].name << endl;
        }
    }


// void tinder::alertCheck(int currTime)
//     {
//     dater* temp;
//     for(int i = 0; i < tableSize; i++)
//         {
//         temp = hashTable[i];

//         while(temp != NULL)
//             {
//             if(temp->alert < currTime)
//                 {
//                 cout << "Alert sent for " << temp->name << endl;
//                 }
//             temp = temp->next;
//             }
//         }
//     }

int tinder::cs()
    {
    return daters.size();
    }
