/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
    Vector< Set<string> >& locations,
    int numHospitals,
    Vector< Set<string> >& result);


void generateAllCombination(Vector<Set<string>>& locations, int start, int numHospitals,
    Vector<Set<string>>& current,
    const Set<string>& cities,
    Vector<Set<string>>& result,
    bool& found);

bool coversAllCities(const Set<string>& cities, const Vector<Set<string>>& hospitals);


int main() {

    Set<string> cities;
    cities.add("A");
    cities.add("B");
    cities.add("C");
    cities.add("D");
    cities.add("E");
    cities.add("F");
    Vector<Set<string>> locations;

    Set<string> hospital1;
    hospital1.add("A");
    hospital1.add("B");
    hospital1.add("C");
    locations.push_back(hospital1);

   
    Set<string> hospital2;
   
    hospital2.add("A");
    hospital2.add("C");
    hospital2.add("D");
    locations.push_back(hospital2);

   
    Set<string> hospital3;
    hospital3.add("B");
    hospital3.add("F");
    locations.push_back(hospital3);

   
    Set<string> hospital4;
    hospital4.add("C");
    hospital4.add("E");
    hospital4.add("A");
    locations.push_back(hospital4);

    int hospitals = 3; 

    Vector<Set<string>> result;

    if (canOfferUniversalCoverage(cities, locations, hospitals, result)) {
        cout << "Coverage is possible with the following hospitals:" << endl;
        for (const auto& s : result) {
            cout << s << endl;
        }
    }
    else {
        cout << "No coverage possible with given number of hospitals." << endl;
    }

    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities,
    Vector< Set<string> >& locations,
    int numHospitals,
    Vector< Set<string> >& result) {

    if (cities.isEmpty()) {
        return true; // all cities already covered
    }
    if (numHospitals == 0) {
        return false; // no hospitals left to use
    }

    Vector<Set<string>> currCombination;
    bool found = false;

    // try all combinations
    generateAllCombination(locations, 0, numHospitals, currCombination, cities, result, found);

    return found;
}

void generateAllCombination(Vector<Set<string>>& locations, int start, int numHospitals,
    Vector<Set<string>>& current,
    const Set<string>& cities,
    Vector<Set<string>>& result,
    bool& found) {
    if (found) {
        return; // solution already found
    }
    if (numHospitals == 0) {
        if (coversAllCities(cities, current)) {
            result = current; // store the valid combination
            found = true;
        }
        return;
    }

    for (int i = start; i < locations.size(); i++) {
        current.add(locations[i]); // choose this location
        generateAllCombination(locations, i + 1, numHospitals - 1, current, cities, result, found);
        current.remove(current.size() - 1); // backtrack
    }
}

bool coversAllCities(const Set<string>& cities, const Vector<Set<string>>& hospitals) {
    Set<string> covered;
    for (Set<string> x : hospitals) {
        covered += x; // collect all covered cities
    }
    return covered == cities; // check if all cities are covered
}