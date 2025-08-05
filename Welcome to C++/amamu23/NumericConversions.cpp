/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    int number = getInteger("Enter an integer: ");
    string strNumber = intToString(number);
    cout << "String representation: " << strNumber << endl;

    string str;
    cout << "Please enter a number as a string: ";
    cin >> str;
    int result = stringToInt(str);
    cout << "Converted integer: " << result << endl;

    return 0;
}

string intToString(int n) {
    
   // You should just write 0 on 0.
    if (n==0) {
        return "0";
    }
    //If it is negative, then write the minus and then multiply by the minus and start the operations as with the positive.
    if (n < 0) {
        return "-" + intToString(-n);
    }
    
    //Let's extract the last digit.
    int ch = n % 10;
    //base case
    if (n < 10) {
        char num = (char)(ch + '0');
        return string() + num;
    }
    //Recursion
    return intToString(n / 10)+(char)(ch+'0');
}
int stringToInt(string str) {
    //base case
    if (str.empty()) {
        return 0;
    }
    int num = str[0] - '0';
    //10th degree corresponding index
    int index = pow(10, str.length() - 1);
    //Recursion
    return num * index+ stringToInt(str.substr(1));
}




