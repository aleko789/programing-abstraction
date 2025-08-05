/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std; 

int flipCount = 0;
int headsInRow = 0;

string Randomize();

int main() {
    cout << Randomize() << endl;
    return 0;
}

string Randomize() {
    //base case(3 heads in a row) 
    if (headsInRow == 3) {
        return "It took " + to_string(flipCount) + " flips to get 3 consecutive heads.";
    }
   // 50 percent heads 50 tails
    bool RandomSide = randomChance(0.5);

    flipCount++;
    //if true it means heads
    if (RandomSide) {
        headsInRow++;
        cout << "heads " << endl;
        //Recursion
        return Randomize();
    }
    //false menans tails
    else {
        //If the head is not raised then it should become zero.
        headsInRow = 0;
        cout << "tails " << endl;
        //Recursion
        return Randomize();
    }
}