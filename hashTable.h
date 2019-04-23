#include <iostream>
#include <string>
#include <chrono>         // std::chrono::seconds
// #include <thread> //FOR MAC
// #include "mingw.thread.h" // std::thread, std::this_thread::sleep_for //FOR PC
#include "User.h"

using namespace std;

class HashTable {
public:
  HashTable(int tableSize);
  ~HashTable();

  bool addNewUser(string _username, string _userFirstName,
                  string _userLastName, string _pin,
                  string _EC_email, string _EC_firstName,
                  string EC_lastName);

  void deleteUser(string _username);

  // Check to make sure usernmame isn't already taken
  bool isInTable(string _username);

  int returnCollisions();
  int returnTotalEvents();
  int returnTableSize();
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
