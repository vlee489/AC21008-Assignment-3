#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> HTSI;
typedef HashNode<string,int> HNSI;

typedef HashTable<string,string> HTSS;
typedef HashNode<string,string> HNSS;

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

bool test1() {
  HTSI T1(117), T2; 
  HNSI N;

  N.assign("AC21008",21008);
  if (N.getKey() != "AC21008" || N.getValue() != 21008) {
    cout << "Hash Node values are not stored correctly";
    return false; 
  }

  T1.insert("Hello",17);
  T1.insert("World",19);
  T1.insert("abc",12);
  if (T1.getValue("Hello") != 17 || T1.getValue("abc")!=12 || T1.getValue("World") != 19) {
    cout << "Values are not stored correctly." << endl;
    return false;
  }

  T2.insert("AAAA",39);
  T2.insert("AAA",42);
  T2.insert("A",76);
  if (T2.getValue("AAAA") != 39 || T2.getValue("A")!=76 || T2.getValue("AAA") != 42) {
    cout << "Values are not stored correctly." << endl;
    return false;
  } 

  HNSS N2;

  N2.assign("AC21008","21008");
  if (N2.getKey() != "AC21008" || N2.getValue() != "21008") {
    cout << "Hash Node values are not stored correctly";
    return false; 
  }

  HTSS T3(97), T4; 
  T3.insert("Hello","17");
  T3.insert("World","19");
  T3.insert("abc","12");
  if (T3.getValue("Hello") != "17" || T3.getValue("abc")!= "12" || T3.getValue("World") != "19") {
    cout << "String values are not stored correctly." << endl;
    return false;
  }

  T4.insert("AAAA","39");
  T4.insert("AAA","42");
  T4.insert("A","76");
  if (T4.getValue("AAAA") != "39" || T4.getValue("A") != "76" || T4.getValue("AAA") != "42") {
    cout << "String values are not stored correctly." << endl;
    return false;
  } 

  return true;
}

int main() {
  if (!test0()) {
    cout << "Test 0 failed." << endl;
    return 1;
  }
  if (!test1()) {
    cout << "Test 1 failed." << endl;
    return 1;
  }
  cout << "Test 1 succeeded." << endl;
  return 0;
}
