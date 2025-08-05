/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int paskal(int, int);

int main() {
    int n = getInteger();
    int k = getInteger();
    cout << paskal(n, k)<<endl;
    return 0;
} 
int paskal(int n, int k ) {
    //base case(It should have come this far in all versions.)
    if ( k == 0 || n==k) {
        return 1;
    }
    else {
        //Recursion
        return paskal(n - 1, k - 1)+paskal(n-1,k);
    }
    
}
