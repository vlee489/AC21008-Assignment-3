#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> HTSI;

bool test0() {
  HTSI hashtable1;
  cout << "1" << endl;
  HTSI hashtable2(113);
  cout << "2" << endl;
  if (hashtable1.size() != 11) { 
    cout << "Default size for a hashtable should be 11." << endl;
    cout << hashtable1.size() << endl;
    return false; 
  }
  if (hashtable2.size() < 113) { 
    cout << "Requested a hash table of size 113, but got a table of a smaller size." << endl;
    cout << hashtable2.size() << endl;
    return false; 
  }
  if (HTSI(12000).size() < 12000) {
    cout << "Requested a hash table of size 12000, but got a table of a smaller size." << endl;
      cout << HTSI(12000).size() << endl;
    return false; 
  }
  return true;
}

int main() {
  if (test0()) {
    cout << "Test 0 completed successfully. " << endl;
    return 0;
  }
  cout << "Test 0 failed." << endl;
  return 1;
}
