
#include <iostream>
#include <string>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "gboggle.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string BIG_BOGGLE_CUBES[25] = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
Vector<string> createCubes(int size);
bool stringIsAlpha(string& str);
void changePlaces(Vector<string>& cubes);
Grid<char> createGrid(Vector<string>& cubes, int boardSize);
void generateAllWords(Set<string>& allWords, Grid<char>& board, Lexicon& lex);
void generate(Grid<char>& board, Grid<bool> visited, Lexicon& lex, int row, int col, string cur, Set<string>& allWords);
bool canMake(string word, Set<string>& allWords);
bool contains(string s, Set<string>& playerWords);
bool findWordPathRecursive(Grid<char>& board, Grid<bool>& visited, string word, int row, int col, int index, Vector<Vector<int>>& path);
Vector<Vector<int>> findWordPath(Grid<char>& board, string word);
void playHumanTurn(Grid<char>& board, Lexicon& lex, Vector<string>& playerWords, int& playerScore, Set<string>& allWords);
void  computerTurn(Set<string>& allWords, Vector<string>& playerWords);

/* Main program */

int main() {
    setRandomSeed(time(NULL));
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    while (true) {
        int boardSize = 4;
        // Ask if user wants 5x5 board
        cout << "Do you want to be your board size 5x5?(Write: yes):";
        string sizeChoice = getLine();

        if (toLowerCase(sizeChoice) == "yes") {
            boardSize = 5;
        }
        // Ask if user wants to enter custom cubes
        bool costum = false;
        cout << "Do you want to enter your own cubes ?(Write: yes): ";
        string cubeChoice = getLine();
        if (toLowerCase(cubeChoice) == "yes") {
            costum = true;
        }

        Vector<string> cubes;
        if (costum) { // User-defined cubes
            cubes = createCubes(boardSize * boardSize);
        }
        else {// Use standard or big cube sets
            if (boardSize == 5) {
                for (int i = 0; i < 25; i++) {
                    cubes.add(BIG_BOGGLE_CUBES[i]);
                }
            }
            else {
                for (int i = 0; i < 16; i++) {
                    cubes.add(STANDARD_CUBES[i]);
                }
            }
        }// Shuffle cube positions
        changePlaces(cubes);
        // Generate board
        Grid<char> board = createGrid(cubes, boardSize);
        // Draw board on screen
        drawBoard(boardSize, boardSize);
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                labelCube(row, col, board[row][col]);
            }
        }// Generate all possible words
        Set<string> allWords;
        Lexicon lex("EnglishWords.dat");
        generateAllWords(allWords, board, lex);
        int playerScore = 0;
        Vector<string> playerWords;
        playHumanTurn(board, lex, playerWords, playerScore, allWords);  // Human turn
        computerTurn(allWords, playerWords);  // Computer turn
        string response; // Ask to play again
        while (true) {
            cout << "Do you want to play again? (yes/no): ";
            response = toLowerCase(trim(getLine()));
            if (response == "yes" || response == "no") break;
            cout << "Please enter 'yes' or 'no'.\n";
        }

        if (response == "no") break;

    }
    return 0;
}

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}
// Let user input custom cube letters
Vector<string> createCubes(int size) {
    Vector<string> ans;
    for (int i = 0; i < size; i++) {
        while (true) {
            cout << "Enter cube " << (i + 1) << " (6 letters): ";
            string cube = getLine();
            cube = toUpperCase(cube);
            if (cube.length() == 6 && stringIsAlpha(cube)) {
                ans.add(cube);
                break;
            }
            else {
                cout << "Invalid input. Please enter exactly 6 letters.\n";
            }
        }
    }
    return ans;
}
// Check if string contains only letters
bool stringIsAlpha(string& str) {
    for (char ch : str) {
        if (!isalpha(ch)) return false;
    }
    return true;
}
// Shuffle cube order randomly
void changePlaces(Vector<string>& cubes) {
    for (int i = 0; i < cubes.size(); i++) {
        int random = randomInteger(i, cubes.size() - 1);
        swap(cubes[i], cubes[random]);
    }
}
// Choose random face from each cube and fill the board
Grid<char> createGrid(Vector<string>& cubes, int boardSize) {
    Grid<char> board(boardSize, boardSize);
    int index = 0;
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            string cube = cubes[index];
            index++;
            int rand = randomInteger(0, 5);
            char ch = cube[rand];
            board[row][col] = ch;
        }
    }
    return board;
}
// Start recursive word generation from every cell
void generateAllWords(Set<string>& allWords, Grid<char>& board, Lexicon& lex) {
    Grid<bool> visited(board.numRows(), board.numCols());
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            generate(board, visited, lex, row, col, "", allWords);
        }
    }
}
// DFS for all valid words from a cell
void generate(Grid<char>& board, Grid<bool> visited, Lexicon& lex, int row, int col, string cur, Set<string>& allWords) {
    if (!board.inBounds(row, col) || visited[row][col]) return;

    cur += board[row][col];

    if (!lex.containsPrefix(cur)) return;

    if (cur.length() >= 4 && lex.contains(cur)) {
        allWords.add(toLowerCase(cur));
    }

    visited[row][col] = true;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x != 0 || y != 0) {
                generate(board, visited, lex, row + x, col + y, cur, allWords);
            }
        }
    }

    visited[row][col] = false;
}

// Check if word exists in board-generated word list
bool canMake(string word, Set<string>& allWords) {
    return allWords.contains(word);
}

// Check if word already entered by player
bool contains(string s, Vector<string>& playerWords) {
    for (string x : playerWords) {
        if (x == s) {
            return true;
        }
    }
    return false;
}

// Player enters words, validate and score them
void playHumanTurn(Grid<char>& board, Lexicon& lex, Vector<string>& playerWords, int& playerScore, Set<string>& allWords) {
    cout << "Enter words (press Enter to finish):" << endl;

    while (true) {
        string word = toLowerCase(trim(getLine()));

        if (word == "") {
            break;
        }
        if (word.length() < 4) {
            cout << "Word must be at least 4 letters long!" << endl;
            continue;
        }

        if (!stringIsAlpha(word)) {
            cout << "Word must contain only letters!" << endl;
            continue;
        }

        if (!lex.contains(word)) {
            cout << "That word is not in the dictionary!" << endl;
            continue;
        }

        if (contains(word, playerWords)) {
            cout << "You have already entered that word!" << endl;
            continue;
        }
        if (!canMake(word, allWords)) {
            cout << "That word can't be formed on the board!" << endl;
            continue;
        }

        playerWords.add(word);
        recordWordForPlayer(word, HUMAN);
        // Highlight word path on board
        Vector<Vector<int>> path = findWordPath(board, word);
        for (Vector<int> step : path) {
            int row = step[0];
            int col = step[1];
            highlightCube(row, col, true);
        }
        pause(500);
        for (Vector<int> step : path) {
            int row = step[0];
            int col = step[1];
            highlightCube(row, col, false);
        }
    }
}
     
// Search board for full word path
Vector<Vector<int>> findWordPath(Grid<char>& board, string word) {
    Grid<bool> visited(board.numRows(), board.numCols());
    for (int r = 0; r < board.numRows(); r++) {
        for (int c = 0; c < board.numCols(); c++) {
            Vector<Vector<int>> path;
            if (findWordPathRecursive(board, visited, word, r, c, 0, path)) return path;
        }
    }
    return {};
}
// DFS to build path for a word
bool findWordPathRecursive(Grid<char>& board, Grid<bool>& visited, string word, int row, int col, int index, Vector<Vector<int>>& path) {
    if (index >= word.length()) return true;
    if (!board.inBounds(row, col) || visited[row][col]) return false;
    if (board[row][col] != toupper(word[index])) return false;

    visited[row][col] = true;
    Vector<int> pair;
    pair.add(row);
    pair.add(col);
    path.add(pair);

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x != 0 || y != 0) {
                if (findWordPathRecursive(board, visited, word, row + x, col + y, index + 1, path)) return true;
            }
        }
    }

    visited[row][col] = false;
    path.remove(path.size() - 1);
    return false;
}
// Computer outputs remaining words and gets points
void  computerTurn(Set<string>& allWords, Vector<string>& playerWords) {
    int computerScore = 0;
    for (string s : playerWords) {
        allWords.remove(s);
   }
    for (string s : allWords) {
        recordWordForPlayer(s, COMPUTER);
    }
}
