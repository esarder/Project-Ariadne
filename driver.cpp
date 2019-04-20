#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include "hashTable.h"
#include "User.h"
// #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for
#include <thread>
#include <sstream>
#include <fstream>
//copy/paste for windows 10 compile--
//g++ -std=c++11 -D _WIN32_WINNT=0x0A00 -o ProjectAriadne.o hashTable.cpp driver.cpp User.cpp
//copy/paste for mac compile--
//g++ -std=c++11 -o ProjectAriadne.o hashTable.cpp driver.cpp User.cpp
using namespace std;


void menu()
    {
    cout << "-------------------------" << endl;
    cout << "ENTER SELECTION" << endl;
    cout << "1. ENTER NAME" << endl;
    cout << "2. PRINT" << endl;
    cout << "3. DISPLAY CURRENT SIZE" << endl;
    cout << "4. ADD EVENT" << endl;
    cout << "5. QUIT" << endl;
    cout << "-------------------------" << endl;
    }

int main()
    {
    int input;
    int number;
    string text;
    HashTable newDate(100);
    bool flag = false;
    string userName, firstName, lastName, ECemail, ECfn, ECln, tempPin;
    User* temp = 0;
    // //test names
    // fstream file;
    // file.open("data.txt");
    // string str;
    // int p = 5;
    // while(getline(file, str))
    //     {
    //     addme = newDate.addMember(p, str);
    //     newDate.addToHash(addme);
    //     p = p+2;
    //     }
    ////////////////////////////////

    while(true)
        {
        menu();
        cin >> input;

        switch(input)
            {
            case 1: //add user function
                while(temp == 0)
                    {
                cin.ignore();
                    cout << "User" << endl;
                    getline(cin, userName);
                    temp = newDate.searchTable(userName);
                    if(temp != 0)
                        {
                        cout << "Username taken! Please enter another username" << endl;
                        }
                    else
                        {
                        break;
                        }
                    temp = 0;

                    }
                cout << "First name: " << endl;
                getline(cin, firstName);
                cout << "Last name: " << endl;
                getline(cin, lastName);
                cout << "Enter emergency contact's email address:" << endl;
                getline(cin, ECemail);
                cout << "Enter emergency contact's first name:" << endl;
                getline(cin, ECfn);
                cout << "Enter emergency contact's last name:" << endl;
                getline(cin, ECln);
                cout << "Enter a 4 digit pin for disabling emergency alerts:" << endl;
                getline(cin, tempPin);

                newDate.addNewUser(userName, firstName, lastName, tempPin, ECemail, ECfn, ECln);

                break;
            case 2: //print list of users
                newDate.print();
                break;
            case 3: //print # of users
                cout << "# of daters: " << newDate.returnTotalUsers() << endl;
                break;
            case 4: //add event
                cout << "Enter Username: " << endl;
                cin.ignore();
                getline(cin, text);
                temp = newDate.searchTable(text);
                temp->addEvent("hike", 10, temp);
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
