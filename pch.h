// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here 
#include <stdlib.h>	// abs
#include <math.h>	// sqrt
#include <vector>	// vector
#include <iostream> // cout
#include <list>		// list
#include <queue>	// priority queue
#include <limits>	// infinity
#include <algorithm> // max

bool isUnique(const char* str);
bool isUnique2(const char* str);
bool checkPermutation(const char* str1, const char * str2);
char * URLify(char* str, size_t len);
bool palindromePermutation(const char* input);
bool oneAway(const char* str1, const char* str2);
void compressString(const char* input, char* output, size_t outputCch);
void rotateImage90(int** bitmap, int width);
void printImage(int** bitmap, int width);
void printPermutations(const char* input);


void testChessBoard();

#endif //PCH_H
