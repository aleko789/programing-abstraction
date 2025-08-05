/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    cout << (isSubsequence("least", "steal") ? "true" : "false") << endl;
    return 0;
}
bool isSubsequence(string text, string subsequence) {

    // If subsequence is empty, it's trivially a subsequence
    if (subsequence.size() == 0) {
        return true;
    }

    // If text is empty but subsequence isn't, return false
    if (text.size() == 0) {
        return false;
    }

    // If first characters match, move both indices forward
    if (text[0] == subsequence[0]) {
        return isSubsequence(text.substr(1), subsequence.substr(1)); 
    }
    else {
        // If they don't match, skip first character in text
        return isSubsequence(text.substr(1), subsequence); 
    }
}
