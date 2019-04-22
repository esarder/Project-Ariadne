INSTRUCTIONS FOR COMPILING:

ON A MAC:

copy/paste for mac compile:
g++ -std=c++11 -o ProjectAriadne.o hashTable.cpp driver.cpp User.cpp
to run:
./ProjectAriadne.o

Make sure that in the User.h and User.cpp files:
#include <thread>  is commented IN! This can be used on macs
#include "mingw.thread.h" is commented OUT! This cannot be used on macs
#include <windows.h> is commented OUT! (This is only in the User.cpp)



ON A PC:

//copy/paste for windows 10 compile:
g++ -std=c++11 -D _WIN32_WINNT=0x0A00 -o ProjectAriadne.o hashTable.cpp driver.cpp User.cpp

Make sure that in the User.h and User.cpp files:
#include <thread>  is commented OUT! This cannot be used on PCs
#include "mingw.thread.h" is commented IN! This can be used on PCs
#include <windows.h> is commented IN! (This is only in the User.cpp)
