//
// Created by Vincent Lee on 15/11/2019.
//
#include <iostream>
#include <string>
#include <fstream>

#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> HTSI;
HTSI hashTable;

/**
 *
 * @param txtFile The text file to read from
 * @param n the number of items that form an N-gram,
 * @param k the number of top most frequent n-grams to output
 * @return 0 for success / error code
 */
int nChar(const string& txtFile, int n, int k){
    if(n < 0 || k < 0){
        cout << "Int pram out of accepted range" << endl;
        return 3;
    }

    string nGram;
    char letter;
    int count = 0;

    ifstream reader(txtFile);
    if( ! reader ) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    // Gets the count of the number of letters
    while(reader.get(letter)) {
        count++;
    }

    int iteratorAmount = (count-n); // stores the number of times we need to go through the file for the nchar
    int iterator = 0;
    int fromChar = -1;
    int toChar = n+1;

    for(int i = 0; i < iteratorAmount; i++){
        while(reader.get(letter)) {
            iterator++;
            //forms the nGram
            if(iterator > fromChar && iterator < toChar){
                nGram.append(reinterpret_cast<const char *>(letter));
            }
            //Has formed the nGram
            if(iterator > toChar){
                if(hashTable.doesContain(nGram)){ // if nGram is already in table
                    int newValue = hashTable.getValue(nGram) + 1;
                    hashTable.erase(nGram);
                    hashTable.insert(nGram, newValue);
                    break;
                }else{// if nGram isn't in table
                    hashTable.insert(nGram, 1);
                    break;
                }
            }

        }
        // reset variable used for each nGram
        iterator = 0;
        nGram = "";
        // Set char to move up one char in list;
        fromChar++;
        toChar++;
    }

    reader.close();
    return 0;
}

int main(){
    nChar("4001414.txt", 3, 10);
    hashTable.printVector();
}
