#include <iostream>
#include <map>

using namespace std;

// restrictions:  it treats every char identical.   upper case, lower case, punctuation are all treated differnetly and non-matching
// a palindrome is a string that has pair characters , such that it can be folded in half and exactly match
// forward and backwards.
bool palindromePermutation(const char* input)
{

	// count the number of occurances for each character 
	map<char, int> charMap;
	int len = strlen(input);
	for (int i = 0; i < len; ++i) {
		charMap[input[i]] += 1;
	}

	// awesome, are there matching pairs for all the chars?
	int countOfNonEven = 0;
	for (auto it = charMap.begin(); it != charMap.end(); ++it) {
		// is it odd?
		if (it->second % 2) {
			// keep track of how many odd counts we have (we might be allowed to have one)
			countOfNonEven += 1;
			// if the len is odd, we are allowed 1 odd char
			// if the len is even, we are allowed 0 odd chars
			if (((len % 2) && countOfNonEven > 1) ||
				(!(len % 2) && countOfNonEven > 0)) {
				// no good!
				return false;
			}
		}
	}

	// it worked!
	return true;
}