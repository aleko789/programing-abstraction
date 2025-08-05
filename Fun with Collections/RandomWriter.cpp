/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

string getFrequentString(map<string, int>& freq);
char generate(const vector<char>& chars);

ifstream openFile(const string& filename);

void getFileInput(string& filename, ifstream& file);

int getMarkovOrder();

string readFileContent(ifstream& file);

void buildMarkovModel(const string& str, int k, map<string, vector<char>>& strChars, map<string, int>& freq);

int main() {
    

    srand(time(0));  // Seed random number generator

    string filename;
    ifstream file;
    getFileInput(filename, file);  // Get the filename and open the file

    int k = getMarkovOrder();  // Get the Markov number

    string str = readFileContent(file);  // Read the content from the file
    file.close();

    map<string, vector<char>> strChars;
    map<string, int> freq;
    buildMarkovModel(str, k, strChars, freq);  // Build the Markov model

    string frequent = getFrequentString(freq);  // Get the most frequent string
    string copy = frequent;
    //if text is less then 2000 symbols
    int failCount = 0;
    // Generate text using the Markov model
    while (copy.size() < 2000 && failCount<20) {
        if (strChars.find(frequent) == strChars.end()) {
            int randomPos = rand() % (str.size() - k);
            frequent = str.substr(randomPos, k);
            failCount++;
            continue;
        }

        char next = generate(strChars[frequent]);

        if (next == '\0') {
            int randomPos = rand() % (str.size() - k);
            frequent = str.substr(randomPos, k);
            failCount++;
            continue;
        }

        copy += next;
        frequent = copy.substr(copy.size() - k);
        failCount = 0;
       

    }

    cout << copy << endl;
    return 0;
}
// Get the filename and open the file
ifstream openFile(const string& filename) {
    ifstream file;
    file.open(filename);
    return file;
}

// Get the file name from the user and ensure it opens successfully
void getFileInput(string& filename, ifstream& file) {
    cout << "Enter the filename: ";
    cin >> filename;
    file = openFile(filename);

    // Retry until file opens successfully
    while (!file.is_open()) {
        cout << "Invalid file. Try again: ";
        cin >> filename;
        file = openFile(filename);
    }
}
// Get the Markov order from the user (1 to 10)
int getMarkovOrder() {
    int k = 0;
    cout << "Enter the markov number: ";
    cin >> k;
    // Ensure the number is within valid range
    while (k < 1 || k > 10) {
        cout << "Number must be from 1 to 10. Try again: ";
        cin >> k;
    }
    return k;
}
// Read the file content into a string
string readFileContent(ifstream& file) {
    string str = "";
    char ch;
    while (file.get(ch)) {
        str += ch;
    }
    return str;
}

// Build the Markov model from the string
void buildMarkovModel(const string& str, int k, map<string, vector<char>>& strChars, map<string, int>& freq) {
    for (int i = 0; i < str.size() - k; i++) {
        string sub = str.substr(i, k);
        char next = str[i + k];
        strChars[sub].push_back(next);  // Add next char to the model
        freq[sub]++;  // Update frequency count
    }
}


// Get the most frequent string from the frequency map
string getFrequentString(map<string, int>& freq) {
    if (freq.empty()) {
        return "";
    }
    string mostFreq = "";
    int maxCount = 0;

    for (const auto& pair : freq) {
        int count = pair.second;
        // Track the string with highest frequency
        if (count > maxCount) {
            maxCount = count;
            mostFreq = pair.first;
        }
    }
    return mostFreq;
}
// Generate a random character from the list of possible characters
char generate(const vector<char>& chars) {
    if (chars.empty()) {
        return '\0';
    }
    int random = rand() % chars.size();  // Randomly choose a character
    return chars[random];
}