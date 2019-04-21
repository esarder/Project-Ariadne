
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
    cout << "6. READ IN USER AND EVENT DATA" << endl;
    cout << "7. QUIT" << endl;
    cout << "-------------------------" << endl;
    }

int main()
    {
    int input;
    int number;
    string text, response;
    HashTable newDate(100);
    bool flag, first = false;
    string userName, firstName, lastName, ECemail, ECfn, ECln, tempPin, event;
    int timer;
    ifstream myfile;
    string filename;

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
            case 6:
                if(first == false){
                  filename = "userData.txt";
                  myfile.open(filename);
                  if (myfile.is_open()){
                  string line;
                  while(getline(myfile, line)){
                    stringstream linestream(line);
                    string user_name, uFN, uLN, uPIN, ECemail,ECfn,ECln;
                    getline(linestream, user_name, ',');
                    getline(linestream, uFN, ',');
                    getline(linestream, uLN, ',');
                    getline(linestream, uPIN, ',');
                    getline(linestream, ECemail, ',');
                    getline(linestream, ECfn, ',');
                    getline(linestream, ECln);
                    bool sucess = newDate.addNewUser(user_name, uFN, uLN, uPIN, ECemail, ECfn, ECln);
                    if(!sucess && user_name != ""){
                      cout << "Could not add user : " << user_name << endl;
                    }
                  }
                  }
                  else{
                  cout << "Failed to open user file." << endl;
                  }
                  myfile.close();

                  filename = "eventData.txt";
                  myfile.open(filename);
                  if (myfile.is_open()){
                  string line;
                  while(getline(myfile, line)){
                    stringstream linestream(line);
                    string user_name, event_name, time;
                    temp = 0;
                    bool found = false;
                    getline(linestream, user_name, ',');
                    getline(linestream, event_name, ',');
                    getline(linestream, time);
                    int int_time = stoi(time);
                    temp = newDate.searchTable(user_name);
                    if(!(temp==NULL)) temp->addEvent(event_name, int_time, temp);
                    else{
                      cout << "Could not find user : " << user_name << endl;
                      cout << "Event name : " << event_name << endl;
                      cout << "Time : " << time <<endl;
                      cout << "Event not added." << endl;
                      }
                    }
                  }
                  else { cout << "Failed to open event file." << endl; }
                  temp = 0;
                  myfile.close();
                  cout << "Would you like to print the new data? Yes/No\n";
                  cin.ignore();
                  getline(cin,response);
                  if(response == "Yes" || response == "yes") newDate.print();
                  first = true;
                }
                else cout << "Already input user and event data\n";
                break;
            case 7: //quit
                cout << "goodbye" << endl;
                return 0;
            default:
                break;
            }
        }
    return 0;
    }

//
//
// #include <chrono>         // std::chrono::seconds
// #include "hashTable.h"
// #include "User.h"
// // #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for
// #include <thread>
// #include <sstream>
// #include <fstream>
// //copy/paste for windows 10 compile--
// //g++ -std=c++11 -D _WIN32_WINNT=0x0A00 -o ProjectAriadne.o hashTable.cpp driver.cpp User.cpp
// //copy/paste for mac compile--
// //g++ -std=c++11 -o ProjectAriadne.o hashTable.cpp driver.cpp User.cpp
// using namespace std;
//
//
// void menu()
//     {
//     cout << "-------------------------" << endl;
//     cout << "ENTER SELECTION" << endl;
//     cout << "1. ADD A USER" << endl;
//     cout << "2. ADD AN TIMED EVENT" << endl;
//     cout << "3. DISPLAY CURRENT SIZE" << endl;
//     cout << "4. PRINT THE HASHTABLE" << endl;
//     cout << "5. READ IN USER AND EVENT DATA" << endl;
//     cout << "6. QUIT" << endl;
//     cout << "-------------------------" << endl;
//     }
//
// int main()
//     {
//     int input;
//     int number;
//     string text;
//     HashTable newDate(100);
//     bool flag, first = false;
//     string userName, firstName, lastName, ECemail, ECfn, ECln, tempPin, response;
//     User* temp = 0;
//     // //test names
//     // fstream file;
//     // file.open("data.txt");
//     // string str;
//     // int p = 5;
//     // while(getline(file, str))
//     //     {
//     //     addme = newDate.addMember(p, str);
//     //     newDate.addToHash(addme);
//     //     p = p+2;
//     //     }
//     ///////////////////////////////
//
//
//     ifstream myfile;
//     string filename;
//     while(true)
//         {
//         menu();
//         cin >> input;
//
//         switch(input)
//             {
//             case 1: //add user function
//                 while(temp == 0)
//                     {
//                       cin.ignore();
//                     cout << "User" << endl;
//                     getline(cin, userName);
//                     temp = newDate.searchTable(userName);
//                     if(temp != 0)
//                         {
//                         cout << "Username taken! Please enter another username" << endl;
//                         }
//                     else
//                         {
//                         break;
//                         }
//                     temp = 0;
//
//                     }
//                 cout << "First name: " << endl;
//                 getline(cin, firstName);
//                 cout << "Last name: " << endl;
//                 getline(cin, lastName);
//                 cout << "Enter emergency contact's email address:" << endl;
//                 getline(cin, ECemail);
//                 cout << "Enter emergency contact's first name:" << endl;
//                 getline(cin, ECfn);
//                 cout << "Enter emergency contact's last name:" << endl;
//                 getline(cin, ECln);
//                 cout << "Enter a 4 digit pin for disabling emergency alerts:" << endl;
//                 getline(cin, tempPin);
//
//                 newDate.addNewUser(userName, firstName, lastName, tempPin, ECemail, ECfn, ECln);
//
//                 break;
//             case 2: //add a timed event
//                 cout << "Enter Username: " << endl;
//                 cin.ignore();
//                 getline(cin, text);
//                 temp = newDate.searchTable(text);
//                 temp->addEvent("hike", 10, temp);
//                 break;
//             case 3: //print # of users
//                 cout << "# of daters: " << newDate.returnTotalUsers() << endl;
//                 break;
//             case 4: //print hashtable
//                 newDate.print();
//                 break;
//             case 5:
//                 if(first == false){
//                   filename = "userData.txt";
//                   myfile.open(filename);
//                   if (myfile.is_open()){
//                   string line;
//                   while(getline(myfile, line)){
//                     stringstream linestream(line);
//                     string user_name, uFN, uLN, uPIN, ECemail,ECfn,ECln;
//                     getline(linestream, user_name, ',');
//                     getline(linestream, uFN, ',');
//                     getline(linestream, uLN, ',');
//                     getline(linestream, uPIN, ',');
//                     getline(linestream, ECemail, ',');
//                     getline(linestream, ECfn, ',');
//                     getline(linestream, ECln);
//                     bool sucess = newDate.addNewUser(user_name, uFN, uLN, uPIN, ECemail, ECfn, ECln);
//                     if(!sucess && user_name != ""){
//                       cout << "Could not add user : " << user_name << endl;
//                     }
//                   }
//                   }
//                   else{
//                   cout << "Failed to open user file." << endl;
//                   }
//                   myfile.close();
//
//                   filename = "eventData.txt";
//                   myfile.open(filename);
//                   if (myfile.is_open()){
//                   string line;
//                   while(getline(myfile, line)){
//                     stringstream linestream(line);
//                     string user_name, event_name, time;
//                     temp = 0;
//                     bool found = false;
//                     getline(linestream, user_name, ',');
//                     getline(linestream, event_name, ',');
//                     getline(linestream, time);
//                     int int_time = stoi(time);
//                     temp = newDate.searchTable(user_name);
//                     if(!(temp==NULL)) temp->addEvent(event_name, int_time, temp);
//                     else{
//                       cout << "Could not find user : " << user_name << endl;
//                       cout << "Event name : " << event_name << endl;
//                       cout << "Time : " << time <<endl;
//                       cout << "Event not added." << endl;
//                       }
//                     }
//                   }
//                   else { cout << "Failed to open event file." << endl; }
//                   temp = 0;
//                   myfile.close();
//                   cout << "Would you like to print the new data? Yes/No\n";
//                   cin.ignore();
//                   getline(cin,response);
//                   if(response == "Yes" || response == "yes") newDate.print();
//                   first = true;
//                 }
//                 else cout << "Already input user and event data\n";
//                 break;
//             case 6: //quit
//                 cout << "goodbye" << endl;
//                 return 0;
//             default:
//                 break;
//             }
//         }
//     return 0;
//     }
