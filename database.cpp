// Title: Lab 2 - database.cpp
//
// Purpose: Implement functions to initialize database, add words, scores and occurrences to database,
//          find information about a word in the database, and find information about the database as
//          a whole.
//
// Class: CSC 2430 Winter 2020
// Author: Andrew McLain

#include "database.h"
#include <string>


// This is the value used to score a word not found in the database
const double neutral = 2.0;

// **Add your implementations for InitDatabase, AddWordToDatabase, FindWordInDatabase, and GetInfoAboutDatabase
// **The information is to stored in the set of parallel arrays: words, occurrenceCounts, scoreTotal
// **which are passed as parameters.  The words array should NOT be sorted, but should not contain any
// **duplicates.  The parameter "size" records the current number of slots of the arrays which are filled.
// **The parameter "capacity" specifies the maximum number of slots in each of the arrays.  If you were to
// **call AddWordToDatabase with a new word, and the current value of "size" was equal to "capacity" the
// **the function would not do the insertion and return false instead of true.

// **Don't forget to add header comments before each function using the following format:
    // **<Describe what this function does
    // Parameters:
    //      **<parameter name> -- <description of parameter>
    //      **<parameter name> -- <description of parameter>
    //      **<parameter name> -- <description of parameter>
    //      ...
    // Returns:
    //      **<describe meaning of return value or put "nothing" if this is a function declared void>
    // Possible Errors:
    //      **<describe possible errors>
//

// This function initializes the database arrays with a size of 0
// Parameters:
//      capacity - maximum size of the array
//      words - array containing each unique word
//      occurrenceCounts - array parallel to words with occurrence count of corresponding word
//      scoreTotals - array parallel to words with combined scores of each word occurrence
//      size - number of elements in each parallel array, current array size.
// Returns:
//      size - initial size of array, which is 0
// Possible Errors:
//      No errors

void InitDatabase(int capacity, string words[], int occurrenceCounts[], int scoreTotals[], int& size){
    size = 0;
}

// This function adds words and scores from a text file (passed as strings) to the database and
// increments occurrence counts appropriately.
// Parameters:
//      capacity - maximum size of the array
//      words - array containing each unique word
//      occurrenceCounts - array parallel to words with occurrence count of corresponding word
//      scoreTotals - array parallel to words with combined scores of each word occurrence
//      size - number of elements in each parallel array, current array size.
//      word - current word being added to the database
//      score - score of current word being added to the database
// Returns:
//      true indicates a word was successfully added, false indicates the database has exceeded capacity
// Possible Errors:
//      Database full

bool AddWordToDatabase(int capacity, string words[], int occurrenceCounts[], int scoreTotals[], int& size,
                       const string& word, int score){
    if(size >= capacity){
        return false;
    }
    for(int i = 0; i < size; i++){
        if(words[i] == word){
            occurrenceCounts[i]++;
            scoreTotals[i] += score;
            return size <= capacity;
        }
    }
    words[size] = word;
    occurrenceCounts[size] = 1;
    scoreTotals[size] = score;
    size++;
    return size <= capacity;
}
// This function finds a word in the database and its corresponding total score, average score
// and occurrence count
// Parameters:
//      words - array containing each unique word
//      occurrenceCounts - array parallel to words with occurrence count of corresponding word
//      scoreTotals - array parallel to words with combined scores of each word occurrence
//      size - number of elements in each parallel array, current array size.
//      word - word being searched
//      occurrences - number of occurrences to be modified
//      averageScore - average review score for the word based on tot. score and # of occurrences
// Returns:
//      no return, modifies occurrences and averageScore
// Possible Errors:
//      No errors
void FindWordInDatabase(const string words[], const int occurrenceCounts[], const int scoreTotals[], int size,
                        const string& word, int& occurrences, double& averageScore){
    unsigned int i;

    if(size == 0){
        occurrences = 0;
        averageScore = neutral;
    }
    else{
        for(i = 0; i < size; i++){
            if(words[i] == word) {
                occurrences = occurrenceCounts[i];
                averageScore = static_cast<double>(scoreTotals[i]) / occurrences;
                break;
            }
            occurrences = 0;
            averageScore = neutral;
        }
    }
}
// This function reports information about the database as a whole, including # of words, as well
// as max # of occurrences, min # of occurrences, max score, and min score for any word.
// Parameters:
//      words - array containing each unique word
//      occurrenceCounts - array parallel to words with occurrence count of corresponding word
//      scoreTotals - array parallel to words with combined scores of each word occurrence
//      size - number of elements in each parallel array, current array size.
//      numberWords - number of words to be modified by the function
//      maxOccurrences - maximum # of occurrences of a word to be modified by function
//      minOccurrences - minimum # of occurrences of a word to be modified by function
//      maxScore - maximum avg. score for any word in the database
//      minScore - minimum avg. score for any word in the database
// Returns:
//      no return, modifies numberWords, maxOccurrences, minOccurrences, maxScore, and minScore
// Possible Errors:
//      No errors
void GetInfoAboutDatabase(const string words[], const int occurrenceCounts[], const int scoreTotals[], int size,
                          int& numberWords, int& maxOccurrences, int& minOccurrences, double& maxScore, double& minScore){
    numberWords = size;
    if(numberWords == 0){
        maxOccurrences = 0;
        minOccurrences = 0;
        maxScore = 0;
        minScore = 0;
    }
    else{
        maxOccurrences = occurrenceCounts[0];
        minOccurrences = occurrenceCounts[0];
        maxScore = static_cast<double>(scoreTotals[0]) / occurrenceCounts[0];
        minScore = static_cast<double>(scoreTotals[0]) / occurrenceCounts[0];

        for(int i = 0; i < size - 1; i++){
            if(occurrenceCounts[i] > maxOccurrences){
                maxOccurrences = occurrenceCounts[i];
            }
            else if(occurrenceCounts[i] < minOccurrences){
                minOccurrences = occurrenceCounts[i];
            }
            if(static_cast<double>(scoreTotals[i]) / occurrenceCounts[i] > maxScore){
                maxScore = static_cast<double>(scoreTotals[i]) / occurrenceCounts[i];
            }
            if(static_cast<double>(scoreTotals[i]) / occurrenceCounts[i] < minScore){
                minScore = static_cast<double>(scoreTotals[i]) / occurrenceCounts[i];
            }
        }
    }
}