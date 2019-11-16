//
// Created by Vincent Lee on 15/11/2019.
//
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>

#include "HashTable.h"

using namespace std;

typedef HashTable<string, int> HTSI;
HTSI hashTable;

/**
 * nGram for chars
 * @param txtFile The text file to read from
 * @param n the number of items that form an N-gram,
 * @param k the number of top most frequent n-grams to output
 * @return 0 for success / error code
 */
int nChar(const string &txtFile, int n, int k) {
    if (n <= 0 || k <= 0) {
        cout << "Int pram out of accepted range" << endl;
        return 3;
    }

    string nGram;
    string inputString;
    char letter;
    int count = 0;

    ifstream reader(txtFile);
    if (!reader) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    // Gets the count of the number of letters
    // and forms a string
    while (reader.get(letter)) {
        count++;
        if (letter == ' ') {
            inputString += '_';
        } else if (letter != '\n') {
            inputString += letter;
        }

    }

    int iteratorAmount = (count - n); // stores the number of times we need to go through the file for the nchar
    int iterator = 0;
    int fromChar = -1;
    int toChar = n;
    int nGramLength = 0;

    for (int i = 0; i < iteratorAmount; i++) {
        for (char &l : inputString) {
            iterator++;
            //forms the nGram
            if (iterator > fromChar && iterator < toChar) {
                nGramLength++;
                nGram += l;
            }
            //Has formed the nGram
            if (nGramLength == n) {
                if (hashTable.doesContain(nGram)) { // if nGram is already in table
                    int newValue = hashTable.getValue(nGram) + 1;
                    hashTable.erase(nGram);
                    hashTable.insert(nGram, newValue);
                } else {// if nGram isn't in table
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

    // END OF nGram COUNTING
    // START OF nGRAM OUTPUT TO SCREEN
    int highestValue = 0;
    int printCounter = k;
    int totalValues = 0;
    // I should be using vectors instead of lists for this
    // welcome to knowing python
    list<int> vectorLocations;
    list<int> tempList;

    // forms a list of all locations with a key/value pair in vector
    // and works out the largest value.
    for (int id = 0; id < hashTable.size(); id++) {
        if (hashTable.getIfFilledAtVector(id)) {
            vectorLocations.push_back(id);
            totalValues += hashTable.getValueAtVector(id);
            if (hashTable.getValueAtVector(id) > highestValue) {
                highestValue = hashTable.getValueAtVector(id);
            }
        }
    }

    while (printCounter > 0) {
        bool hasPrint = false;
        int forTime = (int) vectorLocations.size();
        for (int vID = 0; vID < forTime; vID++) {
            int workingID = vectorLocations.front();
            vectorLocations.pop_front();
            if (hashTable.getValueAtVector(workingID) == highestValue) {
                float frequencyPercentage = (((float) hashTable.getValueAtVector(workingID) / (float) totalValues) *
                                             100);
                printf("%.2f", frequencyPercentage);
                cout << ":" << hashTable.getKeyAtVector(workingID) << endl;
                hasPrint = true;
                printCounter--;
                break;
            } else {
                tempList.push_back(workingID);
            }
        }
        if (!hasPrint) {
            highestValue--;
        }

        for (int q = 0; q < (int) tempList.size(); q++) {
            int placeInt = tempList.front();
            tempList.pop_front();
            vectorLocations.push_back(placeInt);
        }

    }
    return 0;
}

/**
 * nGram for Words
 * @param txtFile The text file to read from
 * @param n the number of items that form an N-gram,
 * @param k the number of top most frequent n-grams to output
 * @return 0 for success / error code
 */
int nWord(const string &txtFile, int n, int k) {
    if (n <= 0 || k <= 0) {
        cout << "Int pram out of accepted range" << endl;
        return 3;
    }

    ifstream reader(txtFile);
    if (!reader) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    string inputString;
    char letter;
    while (reader.get(letter)) {
        if (letter != '\n') {
            inputString += letter;
        }
    }

    // Places each word into a location in the vector
    vector<string> wordList;
    stringstream ss(inputString);
    string vectorWord;
    int count = 0;
    while (getline(ss, vectorWord, ' ')) {
        wordList.push_back(vectorWord);
        count++;
    }

    int iteratorAmount = (count - n); // stores the number of times we need to go through the file for the nchar
    int fromWord = 0;
    int toWord = n;
    string nGram;
    for (int i = 0; i < iteratorAmount; i++) {
        for (int x = fromWord; x < toWord; x++) {
            cout << wordList[x] << endl;
            nGram += wordList[x];
            nGram += ' ';
        }

        if (hashTable.doesContain(nGram)) { // if nGram is already in table
            int newValue = hashTable.getValue(nGram) + 1;
            hashTable.erase(nGram);
            hashTable.insert(nGram, newValue);
        } else {// if nGram isn't in table
            hashTable.insert(nGram, 1);
        }

        // reset variable used for each nGram
        nGram = "";
        // Set char to move up one char in list;
        fromWord++;
        toWord++;
    }

    hashTable.printVector();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 0) {
        nChar("inputfile.txt", 3, 10);
    } else if (argc == 1) {
        string fileName = argv[1];
        nChar(fileName, 3, 10);
    } else if (argc == 2) {
        string fileName = argv[1];
        int nSize = (int) argv[2];
        nChar(fileName, nSize, 10);
    } else if (argc == 3) {
        string fileName = argv[1];
        int nSize = (int) argv[2];
        int kSize = (int) argv[3];
        nChar(fileName, nSize, 3);
    }

}
