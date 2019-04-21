#include <iostream>
#include <string>
#include <cmath>
#include <chrono>         // std::chrono::seconds
#include <thread> //FOR MAC
// #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for //FOR PC

#include "hashTable.h"
#include "User.h"

using namespace std;

// void pause_thread(int n, string name , Event currEvent, User currUser){
//     this_thread::sleep_for (chrono::seconds(n));
//     cout << endl;
//     cout << currUser.getUserFirstName() << "'s alert of " << n;
//     cout << " seconds for " << currEvent.event << " has ended" << endl;
//     currUser.subEventCount();
//     if(currUser.getEventCount()==0){
//       currUser.setInactive();
//       currUser.setSafe();
//     }
//
//     if(currUser.getSafe() == false) //send out email
//         {
//         cout << "send email" << endl;
//         string compile = "a";
//         string firstName = currUser.getEC_firstName();
//         string lastName = currUser.getEC_lastName();
//         string email = currUser.getEC_email();
//         string s1 = compile+" "+firstName+" "+lastName+" "+email;
//
//         //NEED TO UPDATE SYSTEM STUFF
//
//         // system("g++ email2nd.cpp"); //finds and compiles file
//         // system(s1.c_str());//runs file with string variables
//
//         return;
//         }
//     else
//         {
//         cout << currUser.getUserFirstName() << " " << currUser.getUserLastName();
//         cout << " is safe" << endl;
//         cout << "HAAAAA" << endl;
//         return;
//         }
// }

HashTable::HashTable(int tableSize) //done (delete numCollisions)
{
  this->tableSize = tableSize;
  this->numUsers = 0;
  this->numCollisions = 0;

  //initialize hash table and all indecies to 0/NULL
  userHashTable = new User*[tableSize];
  for (int i = 0; i < tableSize; i++){
    userHashTable[i] = 0;
  }
}


HashTable::~HashTable()
{
  for(int i = 0; i < tableSize; i++){
    User* currentUser = userHashTable[i];
    User* tempDelete = 0;

    while(currentUser!=0){
      tempDelete = currentUser;
      currentUser = currentUser->next;
      delete tempDelete;
      tempDelete = 0;
    }
  }
  delete [] userHashTable;
  userHashTable = 0;
}

bool HashTable::isInTable(string _username) //done untested
{
  User* temp = searchTable(_username);
  if(temp == 0){
    return false;
  }
  else{
    return true;
  }
}

bool HashTable::addNewUser(string _username, string _userFirstName,
                            string _userLastName, string _pin,
                            string _EC_email, string _EC_firstName,
                            string _EC_lastName)
{

  if(isInTable(_username)){
    cout << "Username taken! Please enter another username" << endl;
    // How can we have this code repeat to give user another opportunity to create username
    //^^^^^ in driver run a while(temp == 0)
    return false;
  }

  else{
    User* newUser = new User(_username, _userFirstName,
                            _userLastName, _pin,
                            _EC_email, _EC_firstName,
                            _EC_lastName);

    // Adding new user to hashtable
    int index = hash_func(newUser->getUsername());
    User* temp = userHashTable[index];

    if(temp == 0){               // Hashed index is empty - user is first in this index of the hashTable
      newUser->next = 0;
      temp = newUser;
      userHashTable[index] = temp;
    }
    else{                      // User already exits in index of hashtable - must traverse linked list and save user at end
      User* prev = userHashTable[index];

      while(temp!=0){
        prev = temp;
        temp = temp->next;
      }

      if(temp == 0){
        prev->next = newUser;
        newUser->next = 0;
        numCollisions++;
      }
    }
    numUsers++;
    cout << "user: " <<newUser->getUsername() << endl;
    cout << "count: " << newUser->getEventCount() << endl;
    return true;
  }
}

void HashTable::addPreBuiltUser(User newUser){
  if(isInTable(newUser.getUsername())){
    cout << "Username taken! " << newUser.getUsername() << " not added!" << endl;
    return;
  }
  else{
    User* newUser = newUser;

    // Adding new user to hashtable
    int index = hash_func(newUser->getUsername());
    User* temp = userHashTable[index];
    if(temp == 0){               // Hashed index is empty - user is first in this index of the hashTable
      newUser->next = 0;
      temp = newUser;
      userHashTable[index] = temp;
    }
    else{                      // User already exits in index of hashtable - must traverse linked list and save user at end
      User* prev = userHashTable[index];

      while(temp!=0){
        prev = temp;
        temp = temp->next;
      }
      if(temp == 0){
        prev->next = newUser;
        newUser->next = 0;
        numCollisions++;
      }
    }
    numUsers++;
  }
  return;
}

void HashTable::deleteUser(string _username) //uneeded and may cause errors need testing
{
  if(!isInTable(_username)){
    cout << "Username is not present within database" << endl;
  }
  else{
    int index = hash_func(_username);
    User* curr = userHashTable[index];
    User* prev = 0;

    if(curr->getUsername() == _username){
      userHashTable[index] = curr->next;
      // Check this delete - want to make sure I'm not deleting information I need
      delete curr;
      curr = 0;
    }
    else{
      while(curr->getUsername()!=_username){
        prev = curr;
        curr=curr->next;
      }
      if(curr!=0 && prev!=0){
        prev->next = curr->next;
        delete curr;
        curr = 0;
      }
    }
  }
}

void HashTable::print(){ //done
  cout << "Current Daters" << endl;

    User* curr;
    for(int i = 0; i < tableSize; i++)
        {
        curr = userHashTable[i];
        while(curr != NULL)
            {
            cout << "--- " << curr->getUsername() << " ---> ";
            curr = curr->next;
            }
        cout << endl;
        }
}

User* HashTable:: searchTable(string _username) //done untested
{
  int index = hash_func(_username);

  User* curr = userHashTable[index];
  if(curr != 0){
    while(curr!=0){
      if(curr->getUsername() == _username){
        return curr;
      }
      curr=curr->next;
    }
  }

  curr = userHashTable[index-1];
  if(curr != 0){
    while(curr!=0){
      if(curr->getUsername() == _username){
        return curr;
      }
      curr=curr->next;
    }
  }

  return 0;
}

int HashTable::hash_func(string username){
  int hash = 0;
  for(int i=0; i<username.length(); i++){
    hash = hash + username[i]*pow(7, i);
  }
  hash = ((hash*23)+(7*username[4]))%100;
  if (hash<0) return (-1)*hash;
  return hash;
}

int HashTable:: returnCollisions() //done uneeded
{
  return numCollisions;
}

int HashTable:: returnTotalUsers() //done untested
{
  return numUsers;
}
