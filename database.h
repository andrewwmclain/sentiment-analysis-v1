// Title: Lab 2 - database.h
//
// Purpose: Declares the functions that must be used for any attempt to access the word database.
//
// Class: CSC 2430 Winter 2020
// Author: Max Benson

#ifndef SENTIMENT_ANALYSIS_DATABASE_H
#define SENTIMENT_ANALYSIS_DATABASE_H

//
// Please do not change the code below
//
#include <iostream>

using namespace std;

void InitDatabase(int capacity, string words[], int occurrenceCounts[], int scoreTotals[], int& size);
bool AddWordToDatabase(int capacity, string words[], int occurrenceCounts[], int scoreTotals[], int& size,
        const string& word, int score);
void FindWordInDatabase(const string words[], const int occurrenceCounts[], const int scoreTotals[], int size,
        const string& word, int& occurrences, double& averageScore);
void GetInfoAboutDatabase(const string words[], const int occurrenceCounts[], const int scoreTotals[], int size,
        int& numberWords, int& maxOccurrences, int& minOccurrences, double& maxScore, double& minScore);

#endif //SENTIMENT_ANALYSIS_DATABASE_H
