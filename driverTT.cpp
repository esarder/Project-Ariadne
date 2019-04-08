#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include <ctime>
#include <windows.h>
#include <iomanip>
#include "timetest.h"
#include "mingw.thread.h" // std::thread, std::this_thread::sleep_for
#include "mingw.condition_variable.h"
#include "mingw.mutex.h"
#include "mingw.future.h"
#include "mingw.shared_mutex.h"

//copy/paste for windows 10 compile--
// g++ -std=c++11 -D _WIN32_WINNT=0x0A00 timetest.cpp driver.cpp

using namespace std;


void menu()
    {
    cout << "-------------------------" << endl;
    cout << "ENTER SELECTION" << endl;
    cout << "1. ENTER NAME" << endl;
    cout << "2. PRINT" << endl;
    cout << "3. DISPLAY CURRENT SIZE" << endl;
    cout << "4. CANCEL ALERT" << endl;
    cout << "5. QUIT" << endl;
    cout << "-------------------------" << endl;

    }

int main()
    {
    int input;
    int number; 
    string text;
    tinder newDate(10);

    while(true)   
        {
        menu();
        cin >> input;

        switch(input)
            {
            case 1: //add user function
                cout << "Enter alert timer length:" << endl;
                cin >> number;

                cout << "Enter name: " << endl;
                cin.ignore();
                getline(cin, text);
                newDate.addMember(number, text);
                break;
            case 2: //print list of users
                newDate.print();
                break;
            case 3: //print # of users
                cout << "# of daters: " << newDate.cs() << endl;
                break;
            case 4: //cancel alert
                cout << "Enter index: " << endl;
                cin >> number;
                newDate.cancelAlert(number-1);
                break;
            case 5: //quit
                cout << "goodbye" << endl;
                return 0;
            default:
                break;
            }
        }
    return 0;
    }