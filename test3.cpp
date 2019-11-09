#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> HTSI;
typedef HashNode<string,int> HNSI;

typedef HashTable<int,int> HTII;

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

bool test2() {
  HTSI T1(117); 
  int s;

  T1.insert("Hello",17);
  T1.insert("World",19);
  T1.insert("abc",12);
  s = T1.size();
  T1.rehash(2*s);
  if (T1.size() < 2*s) { 
    cout << "rehash does not work correctly." << endl;
    return false;
  }
  if (T1.getValue("Hello") != 17 || T1.getValue("abc")!=12 || T1.getValue("World") != 19) {
    cout << "Values are not stored correctly." << endl;
    return false;
  }

  T1.insert("AAAA",39);
  T1.insert("AAA",42);
  T1.insert("A",76);
  if (T1.getValue("AAAA") != 39 || T1.getValue("A")!=76 || T1.getValue("AAA") != 42) {
    cout << "Values are not stored correctly." << endl;
    return false;
  } 

  T1.erase("AAA");
  T1.erase("World");

  if (T1.getValue("Hello") != 17 || T1.getValue("abc")!=12 || T1.getValue("AAAA") != 39 || T1.getValue("A")!=76) {
    cout << "Values are not stored correctly." << endl;
    return false;
  }

  HTII T3(173); 
  int num = static_cast<int>(T3.size());
  for (int i=0; i<num; i++) {
    T3.insert(9*i*i+11*i+13,2*i-1);
  }
  for (int i=0; i<num; i++) {
    if (T3.getValue(9*i*i+11*i+13) != 2*i-1) {
      cout << "Integer values are not stored correctly." << endl;
      return false;
    }
  }
  for (int i=0; i<num; i=i+2) {
    T3.erase(9*i*i+11*i+13);
  }
  for (int i=1; i<num; i=i+2) {
    if (T3.getValue(9*i*i+11*i+13) != 2*i-1) {
      cout << "Integer values are not stored correctly after erasing." << endl;
      return false;
    }
  }
  for (int i=0; i<num; i=i+2) {
    T3.insert(9*i*i+11*i+13,3*i-1);
  }
  for (int i=0; i<num; i++) {
    if (i%2) {
      if (T3.getValue(9*i*i+11*i+13) != 2*i-1) {
	cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
	return false;
      }
    } else {
      if (T3.getValue(9*i*i+11*i+13) != 3*i-1) {
	cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
	return false;
      }
    }
  }
  return true;
}

bool test3() {
  HTII T3(17); 
  int num = static_cast<int>(200*T3.size());
  for (int i=0; i<num; i++) {
    T3.insert(i,2*i-1);
  }
  if (T3.size() < static_cast<int>(num)) { cout << "Lost some stored values. - Rehashing is not done correctly." << endl; return false; }
  for (int i=0; i<num; i++) {
    if (T3.getValue(i) != 2*i-1) {
      cout << "Integer values are not stored correctly after rehashing." << endl;
      return false;
    }
  }
  for (int i=0; i<num; i=i+2) {
    T3.erase(i);
  }
  for (int i=1; i<num; i=i+2) {
    if (T3.getValue(i) != 2*i-1) {
      cout << "Integer values are not stored correctly after rehashing." << endl;
      return false;
    }
  }
  for (int i=0; i<num; i=i+2) {
    T3.insert(i,3*i-1);
  }
  for (int i=0; i<num; i++) {
    if (i%2) {
      if (T3.getValue(i) != 2*i-1) {
	cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
	return false;
      }
    } else {
      if (T3.getValue(i) != 3*i-1) {
	cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
	return false;
      }      
    }
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
  if (!test2()) {
    cout << "Test 2 failed." << endl;
    return 1;
  }
  if (!test3()) {
    cout << "Test 3 failed." << endl;
    return 1;
  }
  cout << "Test 3 succeeded." << endl;
  return 0;
}
