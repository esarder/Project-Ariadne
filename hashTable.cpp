#include <iostream>
#include <string>
#include <cmath>
#include <chrono>         // std::chrono::seconds
// #include <thread> //FOR MAC
// #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for //FOR PC

#include "hashTable.h"
#include "User.h"

using namespace std;

//initialize hash table and all indecies to 0/NULL
HashTable::HashTable(int tableSize){
  this->tableSize = tableSize;
  this->numUsers = 0;
  this->numCollisions = 0;

  userHashTable = new User*[tableSize];
  for (int i = 0; i < tableSize; i++){
    userHashTable[i] = 0;
  }
}

//class destructor
HashTable::~HashTable(){
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

// Check if a inputted username is in the hashtable
// Returns: bool
bool HashTable::isInTable(string _username){
  User* temp = searchTable(_username);
  if(temp == 0){
    return false;
  }
  else{
    return true;
  }
}

// Add a new user to the hashtable
// Usernames can't be the same but anything else can be
// Returns bool
bool HashTable::addNewUser(string _username, string _userFirstName,
                            string _userLastName, string _pin,
                            string _EC_email, string _EC_firstName,
                            string _EC_lastName){

  if(isInTable(_username)){
    cout << "Username taken! Please enter another username" << endl;
    return false;
  }

  else{
    // Adding new user to hashtable
    User* newUser = new User(_username, _userFirstName,
                            _userLastName, _pin,
                            _EC_email, _EC_firstName,
                            _EC_lastName);

    int index = hash_func(newUser->getUsername());
    User* temp = userHashTable[index];

    if(temp == 0){ // Hashed index is empty - user is first in this index of the hashTable
      newUser->next = 0;
      temp = newUser;
      userHashTable[index] = temp;
    }
    else{ // User already exits in index of hashtable - must traverse linked list and save user at end
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

    return true;
  }
}

void HashTable::deleteUser(string _username){
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

void HashTable::print(){
  cout << endl << "CURRENT USER HASH TABLE" << endl;

  User* curr;
  for(int i = 0; i < tableSize; i++)
      {
      curr = userHashTable[i];
      cout << "[" << i << "]";
      while(curr != NULL)
          {
          cout << "-- " << curr->getUsername() << " --> ";
          curr = curr->next;
          }
      cout << endl;
      }
}

int HashTable::returnTotalEvents(){
  User* curr;
  int totalEvents = 0;
  for(int i = 0; i < tableSize; i++){
      curr = userHashTable[i];
      while(curr != NULL){
        totalEvents = totalEvents + curr->getEventCount();
        curr = curr->next;
        }
      }
  return totalEvents;

}

int HashTable::returnTableSize(){
  return tableSize;
}

User* HashTable::searchTable(string _username){
  int index = hash_func(_username);
  User* curr = userHashTable[index];
  if(curr != 0){
    while(curr!=0){
      if(curr->getUsername() == _username){
        return curr;
      }
      curr=curr->next;
    }
    return 0;
  }
  if(index == 0) return 0;
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

int HashTable::returnCollisions(){
  return numCollisions;
}

int HashTable::returnTotalUsers(){
  return numUsers;
}
