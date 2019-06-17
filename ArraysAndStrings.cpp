// ArraysAndStrings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <map>

using namespace std;

bool isUnique(const char* str)
{
	std::map<char, bool> charMap;

	// empty strings have all unique chars
	if (str == nullptr) 
		return true;

	// loop through the whole string, one char at a time
	for (int i = 0; str[i] != '\0'; ++i)
	{
		// have we seen this char before?
		if (charMap.find(str[i]) == charMap.end())
		{
			// nope, remember it
			charMap[str[i]] = true;
		}
		else
		{
			// yep, that means they are not all unique
			return false;
		}
	}
	return true;
}

bool isUnique2(const char* str)
{
	// empty strings have all unique chars
	if (str == nullptr)
		return true;

	// loop through the whole string, one char at a time
	for (int i = 0; str[i] != '\0'; ++i)
	{
		// does this char repeat?
		for (int j = i+1; str[j] != '\0'; ++j)
		{
			if (str[i] == str[j])
			{
				return false;
			}
		}
	}
	return true;
}

bool checkPermutation(const char* str1, const char * str2)
{
	std::map<char, int> charMap1;

	// find all the chars from the first string, keep a count of them
	for (int i = 0; str1[i] != '\0'; ++i)
	{
		charMap1[str1[i]] += 1;
	}

	// are they same ones in the second string?
	for (int i = 0; str2[i] != '\0'; ++i)
	{
		// see if this char existed in the first string
		int& value = charMap1[str2[i]];
		// nope, fail
		if (value == 0)
			return false;
		// yes, decrement the count
		value--;
		// did we just hit the last one?
		if (value == 0)
		{
			// erase it from the map
			charMap1.erase(str2[i]);
		}
	}

	// if we erased everything from the map they all matched.
	if (charMap1.size() == 0)
		return true;

	// otherwise it's not an anagram
	return false;
}

// note: this modifies str inplace
char * URLify(char* str, size_t len)
{
	for (int i = 0; i < len; ++i)
	{
		// is this a space char?
		if (str[i] == ' ')
		{
			// yup, let's url escape it.  first make space, slide everything down 2 chars
			for (size_t j = len; j > i; j--)
			{
				str[j+2] = str[j];
			}
			// now put in the escape char
			str[i] = '%';
			str[i+1] = '2';
			str[i+2] = '0';
			// now keep track that we just grew the string
			len += 2;
		}
	}
	// make sure it's still terminated
	str[len] = '\0';
	return str;
}


// will return true if:
// adding a single character makes them match 
// deleting a single charactermakes them match 
// changing a single character makes them match


bool oneAwayReplace(const char* str1, const char* str2)
{
	bool changedOne = false;
	for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; ++i) 
	{
		if (str1[i] == str2[i])
			continue;
		if (changedOne)
			return false;
		changedOne = true;
	}
	return true;
}
bool oneAwayInsert(const char* str1, const char* str2)
{
	bool changedOne = false;
	for (int i = 0, j = 0; str1[i] != '\0' && str2[j] != '\0'; ++i, ++j)
	{
		if (str1[i] == str2[j])
			continue;
		if (changedOne)
			return false;
		changedOne = true;
		// insert one in str1
		j += 1;
	}
	return true;
}
bool oneAway1(const char* str1, const char* str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if (len1 == len2)
	{
		return oneAwayReplace(str1, str2);
	}
	else if (len1 == len2 + 1)
	{
		return oneAwayInsert(str1, str2);
	}
	else if (len1 == len2 - 1)
	{
		return oneAwayInsert(str2, str1);
	}
	return false;
}

bool oneAway2(const char* str1, const char* str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	bool changedOne = false;
	if (abs(len1 - len2) > 1)
		return false;
	// which one is shorter?  we are going to treat this always like inserting to str1
	if (len1 > len2)
	{
		swap(str1, str2);
		swap(len1, len2);
	}
	for (int i = 0, j = 0; str1[i] != '\0' && str2[j] != '\0'; ++i, ++j)
	{
		if (str1[i] == str2[j])
			continue;

		if (changedOne)
			return false;
		changedOne = true;

		// if they don't match lengths (match means we are just chaning a char)
		if (len1 != len2)
		{
			// try an insert in str1
			j += 1;
		}
	}
	return true;
}


bool oneAway(const char* str1, const char* str2)
{
	bool b;
	b = oneAway1(str1, str2);
	if (b != oneAway2(str1, str2))
	{
		cout << "bad things; oneAway1 != oneAway2\n";
	}
	return b;
}


// goes through and counts repeated chars.
// aabcccccaaa would become a2b1c5a3
// if the compressed string is larger than input, input is returned
void compressString(const char* input, char * output, size_t outputCch)
{
	char countS[1024];
	int count = 1;
	int i = 0, j = 0;
	for (; input[i] != '\0' && j < outputCch; ++i)
	{
		// do we have a repeating char?
		if (input[i] == input[i + 1])
		{
			count += 1;
			continue;
		}
		// nope, write the output
		output[j++] = input[i];
		_itoa_s(count, countS, sizeof(countS)/sizeof(char), 10);
		for (char* s = countS; *s != '\0'; ++s)
			output[j++] = *s;
		count = 1;
	}
	output[j] = '\0';
	// did it get bigger?
	if (j >= i)
	{
		strcpy_s(output, outputCch * sizeof(char), input);
	}
}

