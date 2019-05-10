// ArraysAndStrings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
char * URLify(char* str, int len)
{
	for (int i = 0; i < len; ++i)
	{
		// is this a space char?
		if (str[i] == ' ')
		{
			// yup, let's url escape it.  first make space, slide everything down 2 chars
			for (int j = len; j > i; j--)
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

int main()
{
	char str[1024];

	// 
	std::cout << "isUnique('abcd')   = \t" << isUnique("abcd") << "\n";
	std::cout << "isUnique('abcda')  = \t" << isUnique("abcda") << "\n";
	std::cout << "isUnique('')       = \t" << isUnique("") << "\n";
	std::cout << "isUnique(nullptr)  = \t" << isUnique(nullptr) << "\n";
	std::cout << "\n";
	//
	std::cout << "isUnique2('abcd')  = \t" << isUnique2("abcd") << "\n";
	std::cout << "isUnique2('abcda') = \t" << isUnique2("abcda") << "\n";
	std::cout << "isUnique2('')      = \t" << isUnique2("") << "\n";
	std::cout << "isUnique2(nullptr) = \t" << isUnique2(nullptr) << "\n";
	std::cout << "\n";
	// 
	std::cout << "checkPermutation('dog', 'god') = \t" << checkPermutation("dog", "god") << "\n";
	std::cout << "checkPermutation('dog', 'god1') = \t" << checkPermutation("dog", "god1") << "\n";
	std::cout << "checkPermutation('dog', 'gog') = \t" << checkPermutation("dog", "gog") << "\n";
	std::cout << "checkPermutation('hero', 'eroh') = \t" << checkPermutation("hero", "eroh") << "\n";
	std::cout << "\n";
	//
	strcpy_s(str, sizeof(str), "this is a test");
	std::cout << "URLify('this is a test') = " << URLify(str, strlen(str)) << "\n";
	strcpy_s(str, sizeof(str), "thisisatest");
	std::cout << "URLify('thisisatest') = " << URLify(str, strlen(str)) << "\n";
	strcpy_s(str, sizeof(str), " thisisatest ");
	std::cout << "URLify(' thisisatest ') = " << URLify(str, strlen(str)) << "\n";
	std::cout << "\n";
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
