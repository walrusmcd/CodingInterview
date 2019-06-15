// ArraysAndStrings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <map>

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

