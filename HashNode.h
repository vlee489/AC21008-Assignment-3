#ifndef MY_HASH_NODE
#define MY_HASH_NODE

using namespace std;

template <class KeyType, class ValueType>
class HashNode {
  KeyType key;     // The hash node's key
  ValueType value; // The key's associated data
  bool isFilled = false;

  /* extend if necessary */

public:

  HashNode();  // constructor
  KeyType getKey() { return key; }
  ValueType getValue() { return value; }
  bool getIsFilled() { return isFilled; }
  void assign(KeyType key, ValueType value);
};

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::assign(KeyType keyIn, ValueType valueIn) {
    key = keyIn;
    value = valueIn;
    isFilled = true;
}

template<class KeyType, class ValueType>
HashNode<KeyType, ValueType>::HashNode() = default;
/*
   Implement the constructor, the assign method
   and any methods that you may additionally need for the HashTable to work.
*/

#endif
