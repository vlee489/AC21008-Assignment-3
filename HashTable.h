#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

template <class KeyType, class ValueType>
class HashTable {
  typedef vector <HashNode<KeyType,ValueType> > Table;
  Table *table; // size of table (# of buckets) is stored in the Table data structure
  int num = 0;   // number of entries stored in the HashTable;

public:
  HashTable();        // constructor, initializes table of size 11;
  HashTable(int);  // constructor, requires size of table as arg
  ~HashTable();       // deconstructor

  int size();      // returns size of the hash table (number of buckets)
  int hash_function(KeyType);     // the table's hash function
  ValueType getValue(KeyType);    // find and return data associated with key

  void insert(KeyType,ValueType); // insert data associated with key into table
  void erase(KeyType);            // remove key and associated data from table

  void rehash(int); // sets a new size for the hash table, rehashes the hash table
  // extend if necessary
};

template <class KeyType, class ValueType>
int HashTable<KeyType,ValueType>::size() {
  return table->size();
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable() {
    table = new Table();
    table->reserve(11);
    table->resize(11);
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(int size) {
    table = new Table();
    table->reserve(size);
    table->resize(size);
}

template<class KeyType, class ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    table->clear();
    delete(table);
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::insert(KeyType keyIn, ValueType valueIn) {
    HashNode<KeyType, ValueType> newNode = HashNode<KeyType, ValueType>();
    newNode.assign(keyIn, valueIn);
    int hash = hash_function(keyIn);
    table->at(hash) = newNode;
    num++;
}

template<class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getValue(KeyType KeyIn) {
    int hash = hash_function(KeyIn);
    HashNode<KeyType, ValueType> workingNode = table->at(hash);
    return workingNode.getValue();
}

/**
 * Hash Function
 * @tparam KeyType
 * @tparam ValueType
 * @return
 */
template<class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::hash_function(KeyType input) {
    int StringSum = 0;
    for (int s = 0; s < input.length(); s++){
        StringSum += input[s];
    }
    int hashMod =  (StringSum) %31;
    return (hashMod/table->size()) %31;
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::erase(KeyType KeyIn) {
    HashNode<KeyType, ValueType> newNode = HashNode<KeyType, ValueType>();
    int hash = hash_function(KeyIn);
    table->at(hash) = newNode;

}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::rehash(int) {
    //to implement
}




/* Implement the 
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/
#endif
