#include <iostream>
#include <string>
#include <cmath>
#include "UserHashTable.hpp"

using namespace std;

//-------->>>> Constructor

HashTable::HashTable(int tableSize)
{
  this->tableSize = tableSize;
  this->numUsers = 0;
  this->numCollisions = 0;

  userHashTable = new User*[tableSize];

  for (int i = 0; i < tableSize; i++){
    userHashTable[i] = 0;
  }

}

//-------->>>> Destructor

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

//-------->>>> isInTable()
bool HashTable::isInTable(string _username)
{
  User* temp = searchTable(_username);
  if(temp == 0){
    return false;
  }
  else{
    return true;
  }
}

//-------->>>> addUser()

void HashTable::addUser(string _username)
{

  if(isInTable(_username)){
    cout << "Username taken! Please enter another username" << endl;
    // How can we have this code repeat to give user another opportunity to create username
  }
  else{

    // Creating user and adding personal information (should this be done in a hashtable function? feels bit odd)
    User* newUser = new User();
    newUser->setUsername(_username);

    string firstName, lastName, tempString;
    int tempPin;


    cout << "User" << endl;
    cout << "First name: " << endl;
    cin >> firstName;
    cout << "Last name: " << endl;
    cin >> lastName;
    newUser->setUser(firstName, lastName);

    //newUser.setFirstName(tempString);
    //newUser.setLastName(tempString);



    cout << endl << "Emergency Contact"<<endl;
    cout << "First name:" << endl;
    cin >> firstName;
    cout << "Last name:" << endl;
    cin >> lastName;
    newUser->setEC_name(firstName, lastName);

    cout << "Enter emergency contact's email address:" << endl;
    cin >> tempString;
    newUser->setEC_email(tempString);

    cout << "Enter a 4 digit pin for disabling emergency alerts:" << endl;
    cin >> tempPin;
    newUser->setPin(tempPin);


    // Adding new user to hashtable
    int index = hash_func(newUser->getUsername());
    User* temp = userHashTable[index];

    if(temp = 0){               // Hashed index is empty - user is first in this index of the hashTable
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
}

//-------->>>> deleteUser()
void HashTable::deleteUser(string _username)
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

//-------->>>> searchTable()
User* HashTable:: searchTable(string _username)
{
  int index = hash_func(_username);
  if (userHashTable[index] == 0){
    return 0;
  }
  else{
    User* curr = userHashTable[index];
    while(curr!=0){
      if(curr->getUsername() == _username){
        break;
      }
      curr=curr->next;
    }
    return curr;
  }
}


//-------->>>> hash_func()
int HashTable::hash_func(string username){
  int hash = 0;
  for(int i=0; i<username.length(); i++){
    hash = hash + username[i]*pow(7, i);
  }
  hash = ((hash*23)+(7*username[4]))%100;
  if (hash<0) return (-1)*hash;
  return hash;
}

//-------->>>> returnCollisions()
int HashTable:: returnCollisions()
{
  return numCollisions;
}

//-------->>>> returnTotalUsers()
int HashTable:: returnTotalUsers()
{
  return numUsers;
}
