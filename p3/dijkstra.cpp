// 
// This program allows the user to manipulate a binary heap.
// The program only inserts string ids with with associated keys
// into the heap. The heap class, however, is capable of storing
// arbitrary pointers along with each heap item.
//

#include <iostream>
#include <string>
#include <cstdlib>

#include "heap.h"

using namespace std;

// Read an integer from standard input; if a non-integer is in the
// buffer, the state is fixed and the user is re-prompted;
// either way, the remainder of the buffer is cleared
void getInteger(string message, int &ref)
{
  bool inputGood = false;
  while (!inputGood) {
    inputGood = true;

    cout << message;
    cin >> ref;

    if (!cin) {
      // Non-integer in input buffer, get out of "fail" state
      cin.clear();
      inputGood = false;
    }
    while (cin.get() != '\n'); // clear buffer
  }
}

int main()
{
  int capacity = 0;
  int option;
  string stringTmp;
  int key, id;
  int retVal;

  cout << "Enter name of graph file: ";
  getline(cin, stringTmp);
  cout << "You entered: " << stringTmp << "\n";
  return 0;
}

