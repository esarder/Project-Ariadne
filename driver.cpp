#include <iostream>       // std::cout
#include <chrono>         // std::chrono::seconds
#include "hashTable.h"
#include "User.h"
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
    cout << "5. MARK SAFE" << endl;
    cout << "6. QUIT" << endl;
    cout << "-------------------------" << endl;
    }

int main()
    {
    int input;
    int number; 
    string text;
    HashTable newDate(100);
    bool flag = false;
    string userName, firstName, lastName, ECemail, ECfn, ECln, tempPin, event;
    int timer;

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
                temp = 0;
                while(temp == 0)
                    {
                    cout << "User" << endl;
                    cin >> userName;
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
                cin >> firstName;
                cout << "Last name: " << endl;
                cin >> lastName;
                cout << "Enter emergency contact's email address:" << endl;
                cin >> ECemail;
                cout << "Enter emergency contact's first name:" << endl;
                cin >> ECfn;
                cout << "Enter emergency contact's last name:" << endl;
                cin >> ECln;
                cout << "Enter a 4 digit pin for disabling emergency alerts:" << endl;
                cin >> tempPin;

                newDate.addNewUser(userName, firstName, lastName, tempPin, ECemail, ECfn, ECln);
                
                break;
            case 2: //print list of users
                newDate.print();
                break;
            case 3: //print # of users
                cout << "# of daters: " << newDate.returnTotalUsers() << endl;
                break;
            case 4: //add event
                temp = 0;
                while(temp == 0)
                    {
                    cout << "Enter Username: " << endl;
                    cin >> text;
                    temp = newDate.searchTable(text);
                    if(temp != 0)
                        {
                        break;
                        }
                    else
                        {
                        cout << "Username not found!" << endl;
                        }
                    }

                cout << "Enter an event name:" << endl;
                cin >> event;
                cout << "Enter countdown time for alert (in seconds):" << endl;
                cin >> timer;

                temp->addEvent(event, timer, temp);
                break;
            case 5: //mark safe
                cout << "Enter Username: " << endl;
                cin >> text;
                temp = newDate.searchTable(text);

                while(text != temp->getPin())
                    {
                    cout << "Enter pin: " << endl;
                    cin >> text;
                    if(text != temp->getPin())
                        {
                        cout << "incorrect pin" << endl;
                        }
                    else
                        {
                        temp->deactivateAlert();
                        }
                    }
                break;
            case 6: //quit
                cout << "goodbye" << endl;
                return 0;
            default:
                break;
            }
        }
    return 0;
    }