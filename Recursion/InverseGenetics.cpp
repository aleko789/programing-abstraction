/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include <vector>
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
void variants(string protein, int index, Map<char, Set<string> >& codons, string res, vector<string>& result);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();

    string protein = "KWS";
    cout << "RNA strands for protein \"" << protein << "\":" << endl;
    listAllRNAStrandsFor(protein, codons);


    /* [TODO: Implement this!] */
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
    vector<string> result;

    // start generating all combinations
    variants(protein, 0, codons, "", result);

    // print all valid RNA strands
    for (string res : result) {
        cout << res << endl;
    }
}

void variants(string protein, int index, Map<char, Set<string> >& codons, string res, vector<string>& result) {
    if (index == protein.length()) {
        // full protein processed, store the RNA sequence
        result.push_back(res);
        return;
    }

    char ch = protein[index];

    // try each codon for current amino acid
    for (string codon : codons[ch]) {
        variants(protein, index + 1, codons, res + codon, result);
    }
}

