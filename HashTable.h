#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY, OUT_OF_VECTOR_RANGE, MEMORY_ALLOCATION_ERROR }; // extend if necessary

template <class KeyType, class ValueType>
class HashTable {
  typedef vector <HashNode<KeyType,ValueType> > Table;
  Table *table; // size of table (# of buckets) is stored in the Table data structure
  Table *newTable; //for storing temp tables
  int num = 0;   // number of entries stored in the HashTable;

public:
  HashTable();        // constructor, initializes table of size 11;
  HashTable(int);  // constructor, requires size of table as arg
  ~HashTable();       // deconstructor

  int size();      // returns size of the hash table (number of buckets)
  int hash_function(KeyType);     // the table's hash function
  int hash_function(KeyType input, int size);
  ValueType getValue(KeyType);    // find and return data associated with key
  bool doesContain(KeyType); // Used to find if a key exists in the vector or not

  void insert(KeyType,ValueType); // insert data associated with key into table
  void erase(KeyType);            // remove key and associated data from table

  void rehash(int); // sets a new size for the hash table, rehashes the hash table
  // extend if necessary
};

template <class KeyType, class ValueType>
int HashTable<KeyType,ValueType>::size() {
  return (int)table->size();
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
    int LoopCounter = 0;
    HashNode<KeyType, ValueType> newNode = HashNode<KeyType, ValueType>();
    newNode.assign(keyIn, valueIn);
    int hash = hash_function(keyIn);
    //cout << "hash: " << hash << "| Key: " << keyIn << "| ValueIn: " << valueIn << "| vectorSize:" << (int)table->size() << endl;
    HashNode<KeyType, ValueType> workingNode;
    if(num > static_cast<long long>((int)table->size()/2)){
        rehash(((int)table->size()*2));
    }
    while(true){
        if(LoopCounter > 1){
            throw DUPLICATE_KEY;
        }
        if(hash < (int)table->size()){
            workingNode = table->at(hash);
            if(!workingNode.getIsFilled()){
                table->at(hash) = newNode;
                num++;
                return;
            }
            if(workingNode.getKey() != keyIn){
                hash++;
            }
        }else{
            hash = 0;
            LoopCounter++;
        }
    }
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::erase(KeyType KeyIn) {
    HashNode<KeyType, ValueType> newNode = HashNode<KeyType, ValueType>();
    int hash = hash_function(KeyIn);
    int LoopCounter = 0;
    //cout << "hash: " << hash << "| KeyToDelete: " << KeyIn << "| vectorSize:" << (int)table->size() << endl;
    HashNode<KeyType, ValueType> workingNode;
    while(true){
        if(LoopCounter > 1){
            throw KEY_NOT_FOUND;
        }
        if(hash < (int)table->size()){
            workingNode = table->at(hash);
            if(workingNode.getKey() == KeyIn){
                table->at(hash) = newNode;
                return;
            }else{
                hash++;
            }
        }else{
            hash = 0;
            LoopCounter++;
        }

    }
}

template<class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getValue(KeyType KeyIn) {
    int LoopCounter = 0;
    int hash = hash_function(KeyIn);
    HashNode<KeyType, ValueType> workingNode;
    while (true) {
        if (LoopCounter > 1) {
            return 0;
        }
        if (hash < (int)table->size()) {
            workingNode = table->at(hash);
            if (workingNode.getKey() != KeyIn) {
                hash++;
            } else if (workingNode.getKey() == KeyIn) {
                return workingNode.getValue();
            }
        }else{
            hash = 0;
            LoopCounter++;
        }
    }
}

/**
 * Hash Function
 * @tparam KeyType
 * @tparam ValueType
 * @return
 */
template<class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::hash_function(KeyType input) {
    hash<KeyType> hashVal;
    int hashKey = (hashVal(input) %31);
    while(hashKey > (int)table->size()){
        hashKey = hashKey/2;
    }
    if(hashKey != 0){
        hashKey--;
    }
    return hashKey;
}

/**
 * Hash Function but custom size definition (Used for rehash)
 * @tparam KeyType
 * @tparam ValueType
 * @param input
 * @param size
 * @return
 */
template<class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::hash_function(KeyType input, int size) {
    hash<KeyType> hashVal;
    int hashKey = (hashVal(input) %31);
    while(hashKey > size){
        hashKey = hashKey/2;
    }
    if(hashKey != 0){
        hashKey--;
    }
    return hashKey;
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::rehash(int newSize) {
    newTable = new Table();
    newTable->reserve(newSize);
    newTable->resize(newSize);
    HashNode<KeyType, ValueType> workingNodeLocal;
    HashNode<KeyType, ValueType> checkingNode;
    int workingHash = 0;
    bool assigned = false;
    while(workingHash < (int)table->size()){
        workingNodeLocal = table->at(workingHash);
        if(workingNodeLocal.getIsFilled()){
            int newHash = hash_function(workingNodeLocal.getKey(), newSize);
            while(!assigned){
                checkingNode = newTable->at(newHash);
                if(!checkingNode.getIsFilled()){
                    newTable->at(newHash) = workingNodeLocal;
                    assigned = true;
                }else{
                    newHash++;
                    if(newHash > (int)newTable->size()){
                        newHash = 0;
                    }
                }
            }
        }
        assigned = false;
        workingHash++;
    }
    table = newTable;
}

/**
 * 
 * @tparam KeyType 
 * @tparam ValueType 
 * @param keyIn The key being searched
 * @return if the key exists in the vector or not
 */
template<class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::doesContain(KeyType keyIn) {
    HashNode<KeyType, ValueType> checkingNode;
    int hash = hash_function(keyIn);
    int LoopCounter = 0;
    while(true){
        checkingNode = table->at(hash);
        if(LoopCounter > 1){
            return false;
        }
        if(hash < table->reserve()){
            if(checkingNode.getKey() == keyIn){
                return true;
            }else{
                hash++;
            }
        }else{
            hash = 0;
            LoopCounter++;
        }
    }
}



/* Implement the 
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/
#endif
