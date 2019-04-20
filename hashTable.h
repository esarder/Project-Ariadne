#include <iostream>
#include <string>
#include <chrono>         // std::chrono::seconds
#include <thread> //FOR MAC
// #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for //FOR PC

#include "User.h"

using namespace std;

class HashTable {
public:
  HashTable(int tableSize);
  ~HashTable();

  // Overload add user to start with multiple kinds of data? Do we only want to call it after we have all the user's information, or
  // let them add it later on?
  bool addNewUser(string _username, string _userFirstName, 
                   string _userLastName, string _pin,
                   string _EC_email, string _EC_firstName, 
                   string EC_lastName);

  void addPreBuiltUser(User newUser);

  void deleteUser(string _username);

  // Check to make sure usernmame isn't already taken
  bool isInTable(string _username);

  int returnCollisions();

  // Returns total number of users in hashtable
  int returnTotalUsers();

  void print();

  User* searchTable(string _username);
private:
  int hash_func(string username);

  User** userHashTable;

  int tableSize;
  int numUsers;
  int numCollisions;


};

const int USER_TABLE_SIZE = 100;
