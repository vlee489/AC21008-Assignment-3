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
 * prints what's ever in the hashtable out
 * in the output stated in brief
 * @param k top x values to show
 */
void printToDisplay(int k) {
    int highestValue = 0;
    int printCounter = k;
    int totalValues = 0;
    // I should be using vectors instead of lists for this
    // welcome to knowing python
    list<int> vectorLocations;
    list<int> tempList;

    int totalEntriesInHashTable = hashTable.getNum();
    if (printCounter > totalEntriesInHashTable) {
        printCounter = totalEntriesInHashTable;
    }

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
                cout << ":" << hashTable.getKeyAtVector(workingID) << "| PrintCounter: " << printCounter << endl;
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
}

/**
 * This is a more effiecent version of the print code
 * 8X more effiecent.
 * prints what's ever in the hashtable out
 * in the output stated in brief
 * @param k top x values to show
 */
void printToDisplayV2(int k){
    int highestValue = 0;
    int printCounter = k;
    int totalValues = 0;

    vector<int> vectorLocations;

    // Used to check the requested amount to display isn't above the number of values in hashtable
    int totalEntriesInHashTable = hashTable.getNum();
    if (printCounter > totalEntriesInHashTable) {
        printCounter = totalEntriesInHashTable;
    }

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

    while(printCounter > 0){
        for (int &item : vectorLocations) {
            if(printCounter <= 0){
                return;
            }
            if (hashTable.getValueAtVector(item) == highestValue) {
                float frequencyPercentage = (((float) hashTable.getValueAtVector(item) / (float) totalValues) *100);
                printf("%.2f", frequencyPercentage);
                cout << ":" << hashTable.getKeyAtVector(item) << "| PrintCounter: " << printCounter << endl;
                printCounter--;
            }
        }
        highestValue--;
    }


}

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

    // Holds vars for input
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

    if (count < n) {
        cout << "not enough input to created desired length of nGram" << endl;
        return 10;
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
                    int newValue = hashTable.getValue(nGram) + 1; // stores new value
                    hashTable.erase(nGram);
                    try {
                        hashTable.insert(nGram, newValue);
                    } catch (...) {
                        cout << "Error inserting: " << nGram << endl;
                    }
                } else {// if nGram isn't in table
                    try {
                        hashTable.insert(nGram, 1);
                    } catch (...) {
                        cout << "Error inserting: " << nGram << endl;
                    }
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
    printToDisplayV2(k);
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
    // Following bool is used to avoid double spaces
    // That can break the nWord processing
    bool justPlacedSpace = false;
    while (reader.get(letter)) {
        if (letter == '.') {
            if (!justPlacedSpace) {
                inputString += ' ';
                justPlacedSpace = true;
            }
        } else if (letter == ',') {
            if (!justPlacedSpace) {
                inputString += ' ';
                justPlacedSpace = true;
            }
        } else if (letter == '!') {
            if (!justPlacedSpace) {
                inputString += ' ';
                justPlacedSpace = true;
            }
        } else if (letter == '?') {
            if (!justPlacedSpace) {
                inputString += ' ';
                justPlacedSpace = true;
            }
        } else if (letter == ' ') {
            if (!justPlacedSpace) {
                inputString += ' ';
                justPlacedSpace = true;
            }
        } else if (letter == '"') {
            if (!justPlacedSpace) {
                inputString += ' ';
                justPlacedSpace = true;
            }
        } else if (letter != '\n') {
            inputString += letter;
            justPlacedSpace = false;
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

    reader.close();

    if (count < n) {
        cout << "not enough input to created desired length of nGram" << endl;
        return 10;
    }

    int iteratorAmount = (count - n) + 1; // stores the number of times we need to go through the file for the nchar
    int fromWord = 0;
    int toWord = n;
    string nGram;
    for (int i = 0; i < iteratorAmount; i++) {
        for (int x = fromWord; x < toWord; x++) {
            // sanity check the int is in range
            if (x >= (int) wordList.size()) {
                cout << "nGram assembled has gone out of range of the vector containing words" << endl;
                return 10;
            }
            nGram += wordList[x];
            nGram += ' ';
        }
        if (hashTable.doesContain(nGram)) { // if nGram is already in table
            int newValue = hashTable.getValue(nGram) + 1;
            hashTable.erase(nGram);
            try {
                hashTable.insert(nGram, newValue);
            } catch (...) {
                cout << "Error inserting: " << nGram << endl;
            }
        } else {// if nGram isn't in table
            try {
                hashTable.insert(nGram, 1);
            } catch (...) {
                cout << "Error inserting: " << nGram << endl;
            }
        }

        // reset variable used for each nGram
        nGram = "";
        // Set char to move up one char in list;
        fromWord++;
        toWord++;
    }

    printToDisplayV2(k);
    return 0;
}

/**
 * nGram for Decimals
 * @param txtFile The text file to read from
 * @param n the number of items that form an N-gram,
 * @param k the number of top most frequent n-grams to output
 * @return 0 for success / error code
 */
int nDecimal(const string &txtFile, int n, int k) {
    if (n <= 0 || k <= 0) {
        cout << "Int pram out of accepted range" << endl;
        return 3;
    }

    ifstream reader(txtFile);
    if (!reader) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    // Gets the count of the number of letters
    // and forms a string
    char letter;
    string inputString;
    while (reader.get(letter)) {
        //this if statment makes sure only numbers are taken in.
        if (letter == '1' || letter == '2' || letter == '3' || letter == '4' || letter == '5' || letter == '6' ||
            letter == '7' || letter == '8' || letter == '9' || letter == '0') {
            inputString += letter;
        }
    }

    // This vector stores each int
    vector<int> intVector;
    int count = 0;
    for (char &c : inputString) {
        try {
            intVector.push_back((int) c);
            count++;
        } catch (...) {
            cout << "Failed to process char: " << "\"" << c << "\"" << endl;
        }
    }

    if (count < n) {
        cout << "not enough input to created desired length of nGram" << endl;
        return 10;
    }

    int iteratorAmount = (count - n) + 1; // stores the number of times we need to go through the file for the nchar
    int fromWord = 0;
    int toWord = n;
    string nGram;
    for (int i = 0; i < iteratorAmount; i++) {
        for (int x = fromWord; x < toWord; x++) {
            // sanity check the int is in range
            if (x >= (int) intVector.size()) {
                cout << "nGram assembled has gone out of range of the vector containing Ints" << endl;
                return 10;
            }
            nGram += (char) intVector[x];
        }
        if (hashTable.doesContain(nGram)) { // if nGram is already in table
            int newValue = hashTable.getValue(nGram) + 1;
            hashTable.erase(nGram);
            try {
                hashTable.insert(nGram, newValue);
            } catch (...) {
                cout << "Error inserting: " << nGram << endl;
            }
        } else {// if nGram isn't in table
            try {
                hashTable.insert(nGram, 1);
            } catch (...) {
                cout << "Error inserting: " << nGram << endl;
            }
        }

        // reset variable used for each nGram
        nGram = "";
        // Set char to move up one char in list;
        fromWord++;
        toWord++;
    }

    printToDisplayV2(k);
    return 0;
}

/**
 * Main method
 * @param argc Number arguments passed in via cmd
 * @param argv  array of argument strings
 * @return error code/success code
 */
int main(int argc, char *argv[]) {
    int nSize;
    int kSize;
    if (argc == 1) {
        nChar("inputfile.txt", 3, 10);
    } else if (argc == 5) {
        string fileName = argv[1];
        try {
            nSize = atoi(argv[2]);
            kSize = atoi(argv[3]);
        } catch (...) {
            cout << "Error parsing values for arguments as ints";
        }
        string mode = argv[4];
        if (mode == "word") {
            return nWord(fileName, nSize, kSize);
        } else if (mode == "char") {
            return nChar(fileName, nSize, kSize);
        } else if (mode == "decimal") {
            return nDecimal(fileName, nSize, kSize);
        } else {
            cout << "Invalid Pram Error" << endl;
            return 20;
        }
    }
}
