#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*TWO SEPARATE HASH FUNCTION. BOTH ARE SET FOR HASH TABLES OF SIZE 100, THOUGH
THIS CAN EASILY BE CHANGED BY UPDATED THE MOD %. PROGRAM WILL RUN FOR TESTS
UNTIL 1 IS ENTERED AS THE USERNAME AND THEN IT WILL PRINT LIST OF ALL HASHES
CREATED TO ENSURE A SOMEWHAT EVEN DISTRIBUTION. HASH FUNCTION TWO IS THE BETTER
ONE I BELIEVE.
*/

/*HASH FUNCTION ONE*/

// int hash_func(string username){
// int hash = 0;
// for(int i=0; i<username.length(); i++){
//   hash = hash + username[i];
// }
// hash = ((hash*23)+(7*username[4]))%100;
// return hash;
// }

/*HASH FUNCTION TWO(PREFERRED)*/

int hash_func(string username){
int hash = 0;
for(int i=0; i<username.length(); i++){
  hash = hash + username[i]*pow(7, i);
}
hash = ((hash*23)+(7*username[4]))%100;
if (hash<0) return (-1)*hash;
return hash;
}

int main(){
vector<int> v;
string un;
bool flag = true;
while(flag){
  cout <<  "enter a username: " << endl;
  getline(cin, un);
  if(un=="1"){
    flag = false;
    break;
  }
  else{
    if(!(un.length() >= 5 && un.length() <=15)){
      cout << "Too long/short, try again!";
    }
    else{
      int tempHash = hash_func(un);
      v.push_back(tempHash);
      cout << tempHash << endl;
    }
  }
}
sort(v.begin(), v.end());
cout << "\nall previous hashes:"<< endl;
for(vector<int>::iterator i = v.begin(); i != v.end(); i++){
  cout << *i << endl;
}
cout << endl << "goodbye!"<< endl << endl;
return 0;
}
