//
// Created by Vincent Lee on 15/11/2019.
//
#include <iostream>
#include <string>
#include <fstream>

#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> HTSI;

/**
 *
 * @param txtFile The text file to read from
 * @param n the number of items that form an N-gram,
 * @param k the number of top most frequent n-grams to output
 * @return 1 for success / error code
 */
int nChar(string txtFile, int n, int k){
    string nGram;
    int count;
    bool nGramExists;

    ifstream reader(txtFile);
    if( ! reader ) {
        cout << "Error opening input file" << endl;
        return 1;
    }
    try {
        HTSI hashTable;
    }catch(...){
        cout << "Error creating Hash Table" << endl;
        return 2;
    }
    if(n < 0 || k < 0){
        cout << "Int pram out of accepted range" << endl;
        return 3;
    }
    

}
