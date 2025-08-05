/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include <queue>
#include <set>
#include "lexicon.h"

using namespace std;

vector<string> findPath(string start, string end, Lexicon &lex);

bool isValidWord(const string& word, const Lexicon& lex, const Lexicon& usedWords);

void printLadder(const vector<string>& ladder);

int main() {
   
    string first = "";
    cout << "Enter start word(RETURN to quit): ";
    cin >> first;
    string last = "";
    cout << "Enter Destination word: ";
    cin >> last;
  
    Lexicon lex("EnglishWords.dat");
   
    vector<string> ladder = findPath(first, last, lex);

    printLadder(ladder);

    return 0;
}
// Performs BFS to find the shortest word ladder from start to end
vector<string> findPath(string first, string last, Lexicon& lex) {
    if (first == last) {
        return { first }; // start and end are the same
    }

    queue<vector<string>> ladder;
    ladder.push({ first });

    Lexicon usedWords;
    usedWords.add(first); // avoid revisiting words

    // While there are still ladders to process
    while (!ladder.empty()) {
        vector<string> currLadder = ladder.front();
        ladder.pop();

        string lastWord = currLadder.back();

        // Generate possible word variations
        for (int i = 0; i < lastWord.size(); i++) {
            string update = lastWord;

            for (char ch = 'a'; ch <= 'z'; ch++) {
                update[i] = ch;
               
            // If the word is valid and not used before
                if (isValidWord(update, lex, usedWords)) {
                    vector<string> newLadder = currLadder;
                    newLadder.push_back(update);

                    // If the target word is found, return the ladder
                    if (update == last) {
                        return newLadder;
                    }

                    usedWords.add(update);
                    ladder.push(newLadder);
                }
            }
        }
    }

    return {}; // no path found
}


// Checks if the word is in the dictionary and hasn't been used yet
bool isValidWord(const string& word, const Lexicon& lex, const Lexicon& usedWords) {
    return lex.contains(word) && !usedWords.contains(word);
}

// Prints the word ladder if found, or a message if not
void printLadder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
        return;
    }

    cout << "Found Ladder: ";
    for (int i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << "->";
    }
    cout << endl;
}



