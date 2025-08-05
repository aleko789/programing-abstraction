/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include "console.h"
#include <iostream>
#include <fstream>
#include "TokenScanner.h"
using namespace std;

bool isVowel(char ch);
int WordsSentences(TokenScanner& scanner, int& words, int& syllables);
int calculateSyllables(string token);
double calculateGrade(int words, int sentences, int syllables);


int main() {
    ifstream file;
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    file.open(filename);
    //It will keep on changing until you get the right one.
    while (!file.is_open()) {
        cout << "Invalid file. Try again: ";
        cin >> filename;
        file.open(filename);
    }
    // read the file.
    TokenScanner scanner;
    scanner.setInput(file);
    scanner.ignoreWhitespace();
    scanner.addWordCharacters("'");

    int words = 0;
    int syllables = 0;
    int sentences = WordsSentences(scanner, words,syllables); 
    double final = calculateGrade(words, sentences, syllables);

    cout << "Sentences: " << sentences << endl;
    cout << "Words: " << words << endl;
    cout << "sil: " << syllables << endl;
    cout << "Grade: " << final << endl;
    file.close();

    return 0;
}

int WordsSentences(TokenScanner& scanner, int& words,int& syllables) {
    int sentences = 0;
    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        //If it starts with the letter
        if (isalpha(token[0])) {
            //Add words.
            words++;
            //count Syllables
            
            syllables += calculateSyllables(token);
               
        }
        //So the sentence is over.
        else if (token == "." || token == "?" || token == "!") {
            sentences++;  
        }
    }
    return sentences;
}

int calculateSyllables(string token) {

    int syllables = 0;
    //I check if the previous one was a vowel or not.
    bool lastVowel = false;
    

    for (int i = 0; i < token.length(); i++) {
        char ch = tolower(token[i]);

        // Check if the character is a vowel
        if (isVowel(ch)) {
            if (!lastVowel) {
                syllables++;
                lastVowel = true;
               
            }
        }
        else {
            lastVowel = false;
           
        }
    }

    // Handle silent 'e' at the end of words 
    if (token.length() > 1 && tolower(token[token.length() - 1]) == 'e' && syllables > 1) {
        syllables--;
    }

    // Every word has at least one syllable
    if (syllables == 0) {
        syllables = 1;
    }

    return syllables;
}

bool isVowel(char ch) {
    ch = tolower(ch);
    //vowels
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y');
}

double calculateGrade(int words, int sentences, int syllables) {
    //Calculating the grade
        double c0 = -15.59;
        double c1 = 0.39;
        double c2 = 11.8;
        return c0 + c1 * ((double)words / sentences) + c2 * ((double)syllables / words);
    }
