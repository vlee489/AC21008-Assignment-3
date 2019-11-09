#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> HTSI;
typedef HashNode<string,int> HNSI;

bool test0() {
  HTSI hashtable1, hashtable2(113);
  HNSI N;
  
  if (hashtable1.size() != 11) { 
    cout << "Default size for a hashtable should be 11." << endl;
    return false; 
  }
  if (hashtable2.size() < 113) { 
    cout << "Requested a hash table of size 113, but got a table of a smaller size." << endl;
    return false; 
  }
  if (HTSI(12000).size() < 12000) {
    cout << "Requested a hash table of size 12000, but got a table of a smaller size." << endl;
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
