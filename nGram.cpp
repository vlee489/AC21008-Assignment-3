//
// Created by Vincent Lee on 15/11/2019.
//
#include <iostream>
#include <string>
#include <fstream>
#include <list>

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
    if(n <= 0 || k <= 0){
        cout << "Int pram out of accepted range" << endl;
        return 3;
    }

    string nGram;
    string inputString;
    char letter;
    int count = 0;

    ifstream reader(txtFile);
    if( ! reader ) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    // Gets the count of the number of letters
    // and forms a string
    while(reader.get(letter)) {
        count++;
        if(letter == ' '){
            inputString += '_';
        }else if(letter != '\n'){
            inputString += letter;
        }

    }

    int iteratorAmount = (count-n); // stores the number of times we need to go through the file for the nchar
    int iterator = 0;
    int fromChar = -1;
    int toChar = n;
    int nGramLength = 0;

    for(int i = 0; i < iteratorAmount; i++){
        for(char& l : inputString) {
            iterator++;
            //forms the nGram
            if(iterator > fromChar && iterator < toChar){
                nGramLength++;
                nGram += l;
            }
            //Has formed the nGram
            if(nGramLength == n){
                cout << "nGram: " << nGram << endl;
                if(hashTable.doesContain(nGram)){ // if nGram is already in table
                    int newValue = hashTable.getValue(nGram) + 1;
                    hashTable.erase(nGram);
                    hashTable.insert(nGram, newValue);
                }else{// if nGram isn't in table
                    hashTable.insert(nGram, 1);
                }
                break;
            }

        }
        // reset variable used for each nGram
        iterator = 0;
        nGram = "";
        nGramLength = 0;
        // Set char to move up one char in list;
        fromChar++;
        toChar++;
    }

    reader.close();

    hashTable.printVector();
    cout << hashTable.size() << endl;

    // END OF nGram COUNTING

    int highestValue = 0;
    int printCounter = k;
    // I should be using vectors instead of lists for this
    // welcome to knowing python
    list <int> vectorLocations;
    list <int> tempList;

    // forms a list of all locations with a key/value pair in vector
    // and works out the largest value.
    for(int id = 0; id < hashTable.size(); id++){
        if(hashTable.getIfFilledAtVector(id)){
            vectorLocations.push_back(id);
            if(hashTable.getValueAtVector(id) > highestValue){
                highestValue = hashTable.getValueAtVector(id);
            }
        }
    }

    while(printCounter > 0){
        bool hasPrint = false;
        int forTime = (int)vectorLocations.size();
        for(int vID = 0; vID < forTime; vID++){
            int workingID = vectorLocations.front();
            vectorLocations.pop_front();
            if(hashTable.getValueAtVector(workingID) == highestValue){
                cout << hashTable.getKeyAtVector(workingID) << ":" << hashTable.getValueAtVector(workingID) << endl;
                hasPrint = true;
                printCounter--;
                break;
            }else{
                tempList.push_back(workingID);
            }
        }
        if(!hasPrint){
            highestValue--;
        }

        for(int q = 0; q < (int)tempList.size(); q++){
            int placeInt = tempList.front();
            tempList.pop_front();
            vectorLocations.push_back(placeInt);
        }

    }


    return 0;

}

int main(){
    nChar("4001714.txt", 3, 10);
}
