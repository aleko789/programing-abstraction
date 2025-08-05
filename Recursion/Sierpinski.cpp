/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
using namespace std;
void drawTriangle(GWindow& gw, GPoint p1, double length);
void draw(GWindow& gw, GPoint p1, double length, int order);

int main() {
    double length;
    int order;

    // Ask user for side length and recursion depth
    cout << "Enter triangle side length: ";
    cin >> length;
    cout << "Enter Sierpinski order: ";
    cin >> order;

    GWindow gw;
    double width = gw.getWidth();
    double height = gw.getHeight();
    double triangleHeight = length * sqrt(3) / 2;

    // Calculate bottom-left corner of the initial triangle (centered)
    GPoint p1(width / 2 - length / 2, height / 2 + triangleHeight / 3);

    // Start recursive drawing
    draw(gw, p1, length, order);

    return 0;
}

void draw(GWindow& gw, GPoint p1, double length, int order) {
    if (order == 0) {
        // Base case: draw a filled triangle
        drawTriangle(gw, p1, length);
    }
    else {
        double half = length / 2;

        // Bottom-left triangle
        draw(gw, p1, half, order - 1);

        // Bottom-right triangle
        GPoint p2(p1.getX() + half, p1.getY());
        draw(gw, p2, half, order - 1);

        // Top triangle
        GPoint p3(p1.getX() + half / 2, p1.getY() - (half * sqrt(3) / 2));
        draw(gw, p3, half, order - 1);
    }
}

void drawTriangle(GWindow& gw, GPoint p1, double length) {
    // Draw equilateral triangle using polar lines
    GPoint p2 = gw.drawPolarLine(p1, length, 0);
    GPoint p3 = gw.drawPolarLine(p2, length, 120);
    gw.drawPolarLine(p3, length, 240);
}