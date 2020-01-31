// Title: Lab 2 - main.cpp
//
// Purpose: Practice using parallel arrays by implementing a naive algorithm for performing
// sentiment analysis on movie reviews.
//
// Class: CSC 2430 Winter 2020
// Author: Andrew McLain

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <chrono>
#include <assert.h>
#include "database.h"

using namespace std;

// Forward declarations
bool BuildDatabase(const string& fileName, int capacity, string words[], int counts[], int scores[], int& size);

//
// Main program:
//
// First prompts the user for a movie review file which is used to generate a database of
// words, each word being stored by a count of its occurrences and the total score
// associated with it.
//
// Then the main program will repeatedly prompt the user to enter a word.  The word
// will be looked up in the movie database, and its average score will be printed.
int main(int argc, char* argv[]) {

    // Declaration of word database structure
    //      NOTE: Main program is only allowed to access
    //      word database using the interface functions
    //      defined in database.h
    const int CAPACITY  = 20000;
    string words[CAPACITY];
    int counts[CAPACITY];
    int scores[CAPACITY];
    int size;
    // End word database structure declaration

    string fileName;
    string review;

    int numberWords;
    int maxOccurrences;
    int minOccurrences;
    double maxScore;
    double minScore;

    string word;

    // For timing BuildDatabase
    chrono::time_point<chrono::steady_clock> start;
    chrono::time_point<chrono::steady_clock> end;

    // Get name of file containing movie reviews. Use
    // 'movieReviews.txt' if user enters blank line.
    cout << "Enter name of movie review file or <ENTER>: ";
    getline(cin, fileName);
    if (fileName.length()== 0) {
        fileName = "movieReviews.txt";
    }

    // Build the word database from movie review file
    // and print how long  it takes to build the database
    start = chrono::steady_clock::now();
    if (!BuildDatabase(fileName, CAPACITY, words, counts, scores, size)) {
        cout << "Database build failure -- you may need to increase the value of CAPACITY." << endl;
        return 0;
    }
    end = chrono::steady_clock::now();
    cout << chrono::duration<double,milli>(end-start).count() << "ms" << endl;

    // Display some information about the database to
    // check if it seems correct
    GetInfoAboutDatabase(words, counts, scores, size, numberWords,
            maxOccurrences, minOccurrences, maxScore, minScore);
    cout << "Number of Words:                   " << numberWords << endl;
    cout << "Max # of occurrences for any word: " << maxOccurrences << endl;
    cout << "Min # of occurrences for any word: " << minOccurrences << endl;
    cout << "Max score for any word:            " << maxScore << endl;
    cout << "Min score for any word:            " << minScore << endl;

    //Now prompt user for words to look up
    cout << "Enter word you want to find the score for or <ENTER>: ";
    getline(cin, word);
    while (word.length() > 0) {
        int count;
        double score;

        FindWordInDatabase(words, counts, scores, size, word, count, score);
        cout << "This word appears " << count << " times, and has an average score of " << score << endl;
        cout << "Enter word you want to find the score for or <ENTER>: ";
        getline(cin, word);
    }
}

// Reads the file consisting of movie review -- one per line, with numerical rating at the start of
// the line.  Breaks the review text into words using blanks as the delimiter, and inserts each
// word into the database along with the rating for the review
// Parameters:
//      filename - name of movie review file
//     **The following parameters are part of the definition of the database data structure
//     **and are simply passed to routines defined in database.h without any interpretation
//          capacity - number of words the database can store
//          words - array of words
//          counts - parallel array of occurrence counts
//          scores - parallel array of score totals
//          size - current number of words in database
// Returns:
//      true indicates database successfully built, false indicates a problem
//  Possible Errors:
//      could not read file
//      database full
bool BuildDatabase(const string& fileName, int capacity, string words[], int counts[], int scores[], int& size) {
    int score;

    string word;
    string line;

    istringstream lineStream;

    ifstream fin;

    fin.open(fileName);
    //If file won't open, output error message and exit function
    if(!fin.is_open()){
        cerr << "Could not open " << fileName << "\n";
        return false;
    }
    //Set database size to 0
    InitDatabase(capacity, words, counts, scores, size);
    //While the file still contains valid input, continue adding words to database
    while(fin.good() && fin >> score){
        lineStream.clear();
        getline(fin, line);
        lineStream.str(line);
        while(lineStream >> word){
            if(!AddWordToDatabase(capacity, words, counts, scores, size, word, score)){
                return false;
            }
        }
    }

    fin.close();
    return true;
}
