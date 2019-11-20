#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>

using namespace std;

enum HashTableError {
    OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY, OUT_OF_VECTOR_RANGE, EMPTY_VECTOR, RESIZE_SMALLER_TABLE
}; // extend if necessary

template<class KeyType, class ValueType>
class HashTable {
    typedef vector<HashNode<KeyType, ValueType> > Table;
    Table *table; // size of table (# of buckets) is stored in the Table data structure
    Table *newTable; //for storing temp tables
    int num = 0;   // number of entries stored in the HashTable;

public:
    HashTable();        // constructor, initializes table of size 11;
    HashTable(int);     // constructor, requires size of table as arg
    ~HashTable();       // deconstructor

    int size();      // returns size of the hash table (number of buckets)
    int hash_function(KeyType);     // the table's hash function
    int hash_function(KeyType input, int size);

    ValueType getValue(KeyType);    // find and return data associated with key
    ValueType getValueAtVector(int); // Gets the value at a certain vector
    KeyType getKeyAtVector(int); // Returns the key at a certain vector;

    bool getIfFilledAtVector(int); // Returns weather a vector has been filled at a certain vector
    bool doesContain(KeyType); // Used to find if a key exists in the vector or not

    void insert(KeyType, ValueType); // insert data associated with key into table
    void erase(KeyType);            // remove key and associated data from table

    void rehash(int); // sets a new size for the hash table, rehashes the hash table
    void printVector(); // prints out vector where the Hashnode is filled.

    int getNum(); // returns num
};

template<class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::size() {
    return (int) table->size();
}

template<class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable() {
    table = new Table();
    table->reserve(11);
    table->resize(11);
    if ((int) table->size() != 11) {
        throw OUT_OF_MEMORY;
    }
}

template<class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(int size) {
    table = new Table();
    table->reserve(size);
    table->resize(size);
    if ((int) table->size() != size) {
        throw OUT_OF_MEMORY;
    }
}

template<class KeyType, class ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    table->clear();
    delete (table);
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::insert(KeyType keyIn, ValueType valueIn) {
    if (doesContain(keyIn)) {
        throw DUPLICATE_KEY;
    }
    int LoopCounter = 0;
    HashNode<KeyType, ValueType> newNode = HashNode<KeyType, ValueType>();
    newNode.assign(keyIn, valueIn);
    int hash = hash_function(keyIn);
    HashNode<KeyType, ValueType> workingNode;
    // if hash table is half filled, we rehash
    if (num > static_cast<long long>((int) table->size() / 2)) {
        rehash(((int) table->size() * 2));
    }

    while (true) {
        if (LoopCounter > 1) {
            throw OUT_OF_MEMORY;
        }
        if (hash < (int) table->size()) {
            workingNode = table->at(hash);
            if (!workingNode.getIsFilled()) {
                table->at(hash) = newNode;
                num++;
                return;
            } else {
                hash++;
            }
        } else {
            // set probe to start of table
            hash = 0;
            LoopCounter++;
        }
    }
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::erase(KeyType KeyIn) {
    if ((int) table->size() <= 0) {
        throw EMPTY_VECTOR;
    }
    HashNode<KeyType, ValueType> newNode = HashNode<KeyType, ValueType>();
    int hash = hash_function(KeyIn);
    int LoopCounter = 0;
    HashNode<KeyType, ValueType> workingNode;
    while (true) {
        if (LoopCounter > 1) {
            throw KEY_NOT_FOUND;
        }
        if (hash < (int) table->size()) {
            workingNode = table->at(hash);
            if (workingNode.getKey() == KeyIn) {
                table->at(hash) = newNode;
                num--;
                return;
            } else {
                hash++;
            }
        } else {
            hash = 0;
            LoopCounter++;
        }

    }
}

template<class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getValue(KeyType KeyIn) {
    if ((int) table->size() <= 0) {
        throw EMPTY_VECTOR;
    }
    int LoopCounter = 0;
    int hash = hash_function(KeyIn);
    HashNode<KeyType, ValueType> workingNode;
    while (true) {
        if (LoopCounter > 1) {
            throw KEY_NOT_FOUND;
        }
        if (hash < (int) table->size()) {
            workingNode = table->at(hash);
            if (workingNode.getKey() != KeyIn) {
                hash++;
            } else if (workingNode.getKey() == KeyIn && workingNode.getIsFilled()) {
                return workingNode.getValue();
            } else {
                hash++;
            }
        } else {
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
    int hashKey = (hashVal(input) % (int) table->size());
    while (hashKey > (int) table->size()) {
        hashKey = hashKey / 2;
    }
    if (hashKey != 0) {
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
    int hashKey = (hashVal(input) % size);
    while (hashKey > size) {
        hashKey = hashKey / 2;
    }
    if (hashKey != 0) {
        hashKey--;
    }
    return hashKey;
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::rehash(int newSize) {
    // catch if user is trying to resize table to the same or smaller size
    if (newSize <= (int) table->size()) {
        throw RESIZE_SMALLER_TABLE;
    }
    if ((int) table->size() <= 0) {
        throw EMPTY_VECTOR;
    }

    newTable = new Table();
    newTable->reserve(newSize);
    newTable->resize(newSize);
    if ((int) newTable->size() != newSize) {
        throw OUT_OF_MEMORY;
    }
    HashNode<KeyType, ValueType> workingNodeLocal;
    HashNode<KeyType, ValueType> checkingNode;
    int workingHash = 0;
    bool assigned = false;
    while (workingHash < (int) table->size()) { // for every item in the old table
        workingNodeLocal = table->at(workingHash); // get the node
        if (workingNodeLocal.getIsFilled()) { // if it has data in the node
            int newHash = hash_function(workingNodeLocal.getKey(), newSize); // get the new hash
            while (!assigned) {
                checkingNode = newTable->at(newHash);
                if (!checkingNode.getIsFilled()) {
                    newTable->at(newHash) = workingNodeLocal;
                    assigned = true;
                } else {
                    newHash++;
                    if (newHash > (int) newTable->size()) {
                        newHash = 0;
                    }
                }
            }
        }
        assigned = false;
        workingHash++;
    }
    delete (table);
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
    if ((int) table->size() <= 0) {
        throw EMPTY_VECTOR;
    }
    HashNode<KeyType, ValueType> checkingNode;

    for(int i =0; i < table->size(); i++){
        checkingNode = table->at(i);
        if(checkingNode.getKey() == keyIn && checkingNode.getIsFilled()){
            return true;
        }
    }
    return false;
}

/**
 * Prints vector with data in it
 * Used for debugging
 * @tparam KeyType
 * @tparam ValueType
 */
template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::printVector() {
    if ((int) table->size() <= 0) {
        throw EMPTY_VECTOR;
    }
    HashNode<KeyType, ValueType> checkingNode;
    for (int v = 0; v < (int) table->size(); v++) {
        checkingNode = table->at(v);
        if (checkingNode.getIsFilled()) {
            cout << "Key:" << checkingNode.getKey() << "| Value: " << checkingNode.getValue() << "| VectorLocation: "
                 << v << "| Filled: " << checkingNode.getIsFilled() << endl;
        }
    }
}

template<class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getValueAtVector(int vectorID) {
    if (vectorID >= (int) table->size()) {
        throw OUT_OF_VECTOR_RANGE;
    }
    HashNode<KeyType, ValueType> checkingNode = table->at(vectorID);
    return checkingNode.getValue();
}

template<class KeyType, class ValueType>
KeyType HashTable<KeyType, ValueType>::getKeyAtVector(int vectorID) {
    if (vectorID >= (int) table->size()) {
        throw OUT_OF_VECTOR_RANGE;
    }
    HashNode<KeyType, ValueType> checkingNode = table->at(vectorID);
    return checkingNode.getKey();
}

template<class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::getIfFilledAtVector(int vectorID) {
    if (vectorID >= (int) table->size()) {
        throw OUT_OF_VECTOR_RANGE;
    }
    HashNode<KeyType, ValueType> checkingNode = table->at(vectorID);
    return checkingNode.getIsFilled();
}

template<class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::getNum() {
    return num;
}


#endif
