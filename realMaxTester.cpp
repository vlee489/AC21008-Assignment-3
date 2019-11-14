#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "HashTable.h"
#include "realMaxTester.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

bool fullPass = true;
bool individualPass = true;

// This is where you can edit the tasks that the tester will perform
// Linker errors may occur if you haven't defined certain methods to avoid this, you may have to comment out the tests you're not using
// or create blank functions used in the header files (maybe needing to return 0)
void tasks()
{
    steveJobsTest0();
    steveJobsTest1();
    steveJobsTest2();
    steveJobsTest3();
}

template <class KeyType, class ValueType>
void printTable(HashTable<KeyType, ValueType> *hashTableObj)
{
    typedef vector<HashNode<KeyType, ValueType>> Table;
    Table *table = hashTableObj->table;
    cout << endl;
    for (int i = 0; i < hashTableObj->size(); i++)
    {
        HashNode<KeyType, ValueType> node = table->at(i);
        // Uncomment out this if statement if something like this isn't present in your program
        if (!node.getBlank())
        {
            cout << "\tHash: " << i << setw(8);
            cout << "\tKey: " << node.getKey() << setw(8);
            cout << "\tValue: " << node.getValue() << setw(8) << endl;
        }
    }
    cout << endl;
}

template <class KeyType, class ValueType>
void printHash(HashTable<KeyType, ValueType> *hashTableObj, KeyType key)
{
    cout << "\tKey: " << key << "\tHash: " << hashTableObj->hash_function(key) << endl;
}

void steveJobsTest0()
{
    cout << endl
         << "Steve Jobs' Test 0: Checks if HashTables are created of appropriate sizes (slightly modified to be harder)" << endl;

    typedef HashTable<string, int> HTSI;
    typedef HashNode<string, int> HNSI;
    HTSI hashtable1, hashtable2(113);
    HNSI N;

    if (hashtable1.size() != 11)
    {
        failIndividual();
    }
    displayTest("Checks default HashTable size is 11");
    cout << endl
         << "\tSize: " + to_string(hashtable1.size()) << endl;

    if (hashtable2.size() != 113)
    {
        failIndividual();
    }
    displayTest("Creates HashTable of size 113");
    cout << endl
         << "\tSize: " + to_string(hashtable2.size()) << endl;

    if (HTSI(12000).size() != 12000)
    {
        failIndividual();
    }
    displayTest("Creates HashTable of size 12000");
    cout << endl
         << "\tSize: " + to_string(HTSI(12000).size()) << endl;
    cout << endl;
}

void steveJobsTest1()
{
    cout << endl
         << "Steve Jobs' Test 1: Checks if HashTables can store values correctly" << endl;

    typedef HashTable<string, int> HTSI;
    typedef HashNode<string, int> HNSI;
    typedef HashTable<string, string> HTSS;
    typedef HashNode<string, string> HNSS;
    HTSI T1(117), T2;
    HNSI N;

    N.assign("AC21008", 21008);
    if (N.getKey() != "AC21008" || N.getValue() != 21008)
    {
        failIndividual();
    }
    displayTest("Creates HashNode with Key of \"AC21008\" and integer value of 21008 and gets the value back");
    cout << endl
         << "\tKey: " << N.getKey() << setw(8) << "\tValue: " << N.getValue() << endl;

    T1.insert("Hello", 17);
    T1.insert("World", 19);
    T1.insert("abc", 12);
    if (T1.getValue("Hello") != 17 || T1.getValue("abc") != 12 || T1.getValue("World") != 19)
    {
        failIndividual();
    }
    displayTest("Inserts integers onto HashTable of size 117 with keys as strings and gets the values back");
    cout << endl
         << "\tValue 1: " << T1.getValue("Hello") << setw(8) << "\tValue 2: " << T1.getValue("abc") << setw(8) << "\tValue 3: " << T1.getValue("World") << endl;

    T2.insert("AAAA", 39);
    T2.insert("AAA", 42);
    T2.insert("A", 76);
    if (T2.getValue("AAAA") != 39 || T2.getValue("A") != 76 || T2.getValue("AAA") != 42)
    {
        failIndividual();
    }
    displayTest("Inserts integers onto HashTable of default size with keys as strings and gets the values back");
    cout << endl
         << "\tValue 1: " << T2.getValue("AAAA") << setw(8) << "\tValue 2: " << T2.getValue("AAA") << setw(8) << "\tValue 3: " << T2.getValue("A") << endl;

    HNSS N2;

    N2.assign("AC21008", "21008");
    if (N2.getKey() != "AC21008" || N2.getValue() != "21008")
    {
        failIndividual();
    }
    displayTest("Creates HashNode with Key of \"AC21008\" and value of \"21008\" and gets the value back");
    cout << endl
         << "\tKey: " << N2.getKey() << setw(8) << "\tValue: " << N2.getValue() << endl;

    HTSS T3(97), T4;
    T3.insert("Hello", "17");
    T3.insert("World", "19");
    T3.insert("abc", "12");
    if (T3.getValue("Hello") != "17" || T3.getValue("abc") != "12" || T3.getValue("World") != "19")
    {
        failIndividual();
    }
    displayTest("Inserts strings onto HashTable of size 97 with keys as strings and gets the values back");
    cout << endl
         << "\tValue 1: " << T3.getValue("Hello") << setw(8) << "\tValue 2: " << T3.getValue("abc") << setw(8) << "\tValue 3: " << T3.getValue("World") << endl;

    T4.insert("AAAA", "39");
    T4.insert("AAA", "42");
    T4.insert("A", "76");
    if (T4.getValue("AAAA") != "39" || T4.getValue("A") != "76" || T4.getValue("AAA") != "42")
    {
        failIndividual();
    }
    displayTest("Inserts strings onto HashTable of default size with keys as strings and gets the values back");
    cout << endl
         << "\tValue 1: " << T4.getValue("AAAA") << setw(8) << "\tValue 2: " << T4.getValue("AAA") << setw(8) << "\tValue 3: " << T4.getValue("A") << endl;

    cout << endl;
}

void steveJobsTest2()
{
    cout << endl
         << "Steve Jobs' Test 2: Tests Rehashing and Erasing using mostly large data sets" << endl;

    typedef HashTable<string, int> HTSI;
    typedef HashTable<int, int> HTII;

    HTSI T1(117);
    int s;

    T1.insert("Hello", 17);
    T1.insert("World", 19);
    T1.insert("abc", 12);
    s = T1.size();
    T1.rehash(2 * s);
    if (T1.size() < 2 * s)
    {
        failIndividual();
    }
    displayTest("Rehashes HashTable from size 117 to 234");
    cout << endl
         << "\tSize: " << T1.size();
    cout << endl;

    if (T1.getValue("Hello") != 17 || T1.getValue("abc") != 12 || T1.getValue("World") != 19)
    {
        failIndividual();
    }
    displayTest("Checks that HashNodes present before rehashing can still be accessed");
    cout << endl
         << "\tValue 1: " << T1.getValue("Hello") << setw(8) << "\tValue 2: " << T1.getValue("abc") << setw(8) << "\tValue 3: " << T1.getValue("World");
    cout << endl;
    // printTable(&T1);
    // printHash<string, int>(&T1, "World");

    T1.insert("AAAA", 39);
    T1.insert("AAA", 42);
    T1.insert("A", 76);
    if (T1.getValue("AAAA") != 39 || T1.getValue("A") != 76 || T1.getValue("AAA") != 42)
    {
        // cout << "Values are not stored correctly." << endl;
        failIndividual();
    }
    displayTest("Inserts strings onto HashTable with keys as strings and gets the values back");
    cout << endl
         << "\tValue 1: " << T1.getValue("AAAA") << setw(8) << "\tValue 2: " << T1.getValue("AAA") << setw(8) << "\tValue 3: " << T1.getValue("A");
    cout << endl;

    T1.erase("AAA");
    T1.erase("World");

    if (T1.getValue("Hello") != 17 || T1.getValue("abc") != 12 || T1.getValue("AAAA") != 39 || T1.getValue("A") != 76)
    {
        // cout << "Values are not stored correctly." << endl;
        failIndividual();
    }
    displayTest("Erases some nodes and checks that other nodes are still accessible");
    cout << endl
         << "\tValue 1: " << T1.getValue("Hello") << setw(8) << "\tValue 2: " << T1.getValue("abc") << setw(8) << "\tValue 3: " << T1.getValue("AAAA") << setw(8) << "\tValue 4: " << T1.getValue("A");
    cout << endl;

    HTII T3(173);
    int num = static_cast<int>(T3.size());
    for (int i = 0; i < num; i++)
    {
        T3.insert(9 * i * i + 11 * i + 13, 2 * i - 1);
    }
    for (int i = 0; i < num; i++)
    {
        if (T3.getValue(9 * i * i + 11 * i + 13) != 2 * i - 1)
        {
            // cout << "Integer values are not stored correctly." << endl;
            failIndividual();
            // cout << endl;
        }
    }
    displayTest("Inserts 173 items with keys and values as intergers on a HashTable of the same size and tries to retrieve the values back");
    cout << endl;
    // printTable(&T3);

    for (int i = 0; i < num; i = i + 2)
    {
        T3.erase(9 * i * i + 11 * i + 13);
    }
    for (int i = 1; i < num; i = i + 2)
    {
        if (T3.getValue(9 * i * i + 11 * i + 13) != 2 * i - 1)
        {
            // cout << "Integer values are not stored correctly after erasing." << endl;
            failIndividual();
            // cout << endl;
        }
    }
    displayTest("Erases half the items and tries to retrieve the values from the items that haven't been deleted");
    cout << endl;
    // printTable(&T3);

    for (int i = 0; i < num; i = i + 2)
    {
        T3.insert(9 * i * i + 11 * i + 13, 3 * i - 1);
    }
    for (int i = 0; i < num; i++)
    {
        if (i % 2)
        {
            if (T3.getValue(9 * i * i + 11 * i + 13) != 2 * i - 1)
            {
                // cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
                failIndividual();
                // cout << endl;
            }
        }
        else
        {
            if (T3.getValue(9 * i * i + 11 * i + 13) != 3 * i - 1)
            {
                // cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
                failIndividual();
                // cout << endl;
            }
        }
    }
    displayTest("Restores the erased nodes and tries to retrieve their values");
    cout << endl;

    cout << endl;
}

void steveJobsTest3()
{
    typedef HashTable<int, int> HTII;

    cout << endl
         << "Steve Jobs' Test 3: " << endl;

    HTII T3(17);
    int num = static_cast<int>(200 * T3.size());
    for (int i = 0; i < num; i++)
    {
        T3.insert(i, 2 * i - 1);
    }
    if (T3.size() < static_cast<int>(num))
    {
        // cout << "Lost some stored values. - Rehashing is not done correctly." << endl;
        failIndividual();
    }
    displayTest("Checks for automatic rehashing when more nodes are inserted than the size of the HashTable");
    cout << endl;

    for (int i = 0; i < num; i++)
    {
        if (T3.getValue(i) != 2 * i - 1)
        {
            // cout << "Integer values are not stored correctly after rehashing." << endl;
            failIndividual();
        }
    }
    displayTest("Checks that stored elements can be retrieved after rehashing");
    cout << endl;

    for (int i = 0; i < num; i = i + 2)
    {
        T3.erase(i);
    }
    for (int i = 1; i < num; i = i + 2)
    {
        if (T3.getValue(i) != 2 * i - 1)
        {
            // cout << "Integer values are not stored correctly after rehashing." << endl;
            failIndividual();
        }
    }
    displayTest("Erases every second element from the third (e.g. counting from 0, elements 2, 4, 6,... are deleted)\n\tand checks that elements that haven't been erased can still be retrieved");
    cout << endl;

    for (int i = 0; i < num; i = i + 2)
    {
        T3.insert(i, 3 * i - 1);
    }
    for (int i = 0; i < num; i++)
    {
        if (i % 2)
        {
            if (T3.getValue(i) != 2 * i - 1)
            {
                // cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
                failIndividual();
            }
        }
        else
        {
            if (T3.getValue(i) != 3 * i - 1)
            {
                // cout << "Integer values are not stored correctly after erasing and reinserting." << endl;
                failIndividual();
            }
        }
    }
    displayTest("");
    cout << endl;
}

void displayIntro()
{
    system("clear");
    cout << "Real Max Tester for Assignment 3 in Computer Systems 2A" << endl;
    cout << "Use wisely" << endl;
}

void displayTest(string str)
{
    cout << endl;
    if (individualPass)
    {
        cout << "\033[32m"
             << "[PASS]";
        cout << "\033[0m"
             << "\t" << str;
    }
    else
    {
        cout << "\033[31m"
             << "[FAIL]";
        cout << "\033[39;49m"
             << "\t" << str;
        individualPass = true;
    }
}

void roast()
{
    int randVal = rand() % 2;
    switch (randVal)
    {
    case 0:
        cout << "You code is worse than Uncle Ian's memes" << endl;
        break;
    case 1:
        cout << "If this program marked you like Mike Crabbs, you'd just fail the module" << endl;
        break;
    default:
        cout << "Whatever you think is causing this, it's not the problem" << endl;
    }
}

void concern()
{
    int randVal = rand() % 2;
    switch (randVal)
    {
    case 0:
        cout << "Your limitation — it’s only your imagination";
        break;
    default:
        cout << "Push yourself, because no one else is going to do it for you.";
        break;
    }
}

void displayFail()
{
    cout << R"(
        ______      _  _ 
        |  ___|    (_)| |
        | |_  __ _  _ | |
        |  _|/ _` || || |
        | | | (_| || || |
        \_|  \__,_||_||_|            
    )";
    cout << endl;
}

void displayPass()
{
    cout << R"(
         _____            
        /  ___|                                 
        \ `--.  _   _   ___  ___  ___  ___  ___ 
         `--. \| | | | / __|/ __|/ _ \/ __|/ __|
        /\__/ /| |_| || (__| (__|  __/\__ \\__ \
        \____/  \__,_| \___|\___|\___||___/|___/
    )";
    cout << endl;
}

void failIndividual()
{
    fullPass = false;
    individualPass = false;
}

void oops(int sig)
{
    failIndividual();
    cout << "Oops there's a fault here: " << sig << endl;
    displayFail();
    int randVal = rand() % 100;

    if (randVal < 15)
    {
        roast();
    }
    else if (randVal < 30)
    {
        concern();
    }
}

int catchSegFault()
{
    struct sigaction act;
    act.sa_handler = oops;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);
    return 0;
}

void checkSuccess()
{
    if (fullPass)
    {
        displayPass();
    }
    else
    {
        displayFail();
    }
}

int main()
{
    catchSegFault();
    displayIntro();
    tasks();
    checkSuccess();
    return 0;
}