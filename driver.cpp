
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
    cout << "1. ADD A USER" << endl;
    cout << "2. ADD AN EVENT" << endl;
    cout << "3. MARK SAFE / DEACTIVATE EVENT" << endl;
    cout << "4. PRINT USER EVENTS" << endl;
    cout << "5. DELETE A USER" << endl;
    cout << "6. PRINT USER HASH TABLE" << endl;
    cout << "7. VIEW HASH TABLE STATS" << endl;
    cout << "8. READ IN USER AND EVENT DATA" << endl;
    cout << "9. QUIT" << endl;
    cout << "-------------------------" << endl;
    }

void intro(){
  cout << "\n\nWelcome to the Ariadne Project\n\n";
  cout << "In Greek mythology, Ariadne was the Cretan princess who gave Theseus\n";
  cout << "the yarn he used to record his path in the labyrinth while he defeated\n";
  cout << "the minotaur.\n\n";
  cout << "Like Ariadne, we want to be able to give people the ability leave a\n";
  cout << "trail which can be followed should life take an unexpected turn.\n\n";
  return;
}

//ensure PIN meets criteria
bool setPin(string pin){
    if(pin.length()!=4){
        return false;
      }
    for(int i=0; i<4; i++){
        if(!(pin[i] >= 48 && pin[i] <= 57)) return false;
      }
    return true;
  }

int main()
    {
    //greet users
    intro();
    int input, number, timer;
    string text, response, response1;
    HashTable userTable(100);
    bool flag, first, works = false;
    string userName, firstName, lastName, ECemail, ECfn, ECln, tempPin, event;
    ifstream myfile;
    string filename;
    User* temp = 0;

    while(true)
        {
        menu();
        cin >> input;

        switch(input)
            {
            case 1: //add user
                temp = 0;
                while(temp == 0)
                    {
                    cout << "Enter a username: ";
                    cin >> userName;
                    temp = userTable.searchTable(userName);
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
                works = setPin(tempPin);
                while(!works){
                  cout << "PIN must be four digits.\nEnter PIN: ";
                  cin >> tempPin;
                  works = setPin(tempPin);
                }
                if(!(userTable.addNewUser(userName, firstName, lastName, tempPin, ECemail, ECfn, ECln))){
                  cout << "User could not be created!\n";
                }
                break;
            case 2: //add an event
              temp = 0;
              while(temp == 0)
                  {
                  cout << "Enter Username: " << endl;
                  cin >> text;
                  temp = userTable.searchTable(text);
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
            case 3: //deactivate an alert
                cout << "Enter Username: " << endl;
                cin >> text;
                temp = userTable.searchTable(text);

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
            case 4: //printer user event
                cout << "Enter a username: ";
                cin.ignore();
                cin >> userName;
                temp = userTable.searchTable(userName);
                if(temp == 0) cout << "User not found\n";
                else{
                  temp->printEvents();
                }
                break;
            case 5: //delete user
                cout << "In order to delete a user you will need their username and PIN.\n";
                cout << "username: ";
                cin >> text;
                cout << "PIN: ";
                cin >> response;
                temp = userTable.searchTable(text);
                if(response == temp->getPin() && temp != 0){
                  userTable.deleteUser(text);
                  cout << text << " sucessfully deleted\n";
                }
                else if(temp==0) cout << "User not found\n";
                else if(response != temp->getPin()) cout << "Invalid PIN\n";
                break;
            case 6: //print the hashtable
                userTable.print();
                break;
            case 7: //display hash table stats
                cout << "Number of users: " << userTable.returnTotalUsers() << endl;
                cout << "Number of events: " << userTable.returnTotalEvents() << endl;
                cout << "Number of collisions: " << userTable.returnCollisions() << endl;
                cout << "Hashtable size: " << userTable.returnTableSize() << endl;
                break;
            case 8://read in user and event data
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
                    bool sucess = userTable.addNewUser(user_name, uFN, uLN, uPIN, ECemail, ECfn, ECln);
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
                    temp = userTable.searchTable(user_name);
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
                  if(response == "Yes" || response == "yes") userTable.print();
                  first = true;
                }
                else cout << "Already input user and event data\n";
                break;
            case 9: //quit
                cout << "goodbye" << endl;
                return 0;
            default:
                break;
            }
        }
    return 0;
    }
