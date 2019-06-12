#include <iostream>

using namespace std;

namespace StringPermutate
{
	void swap(char* s1, char* s2)
	{
		char ch = *s1;
		*s1 = *s2;
		*s2 = ch;
	}


	void printOption(char* output, int start, int len, int* totalOptions)
	{
		// are we done?
		if (start == len)
		{
			// print the permutation
			cout << output << "\n";
			*totalOptions += 1;
			return;
		}
		// go through the rest of the string
		for (int i = start; i < len; ++i)
		{
			// swap this char
			swap(output, output + i);
			printOption(output, start + 1, len, totalOptions);
			swap(output, output + i);
		}
	}
}

void printPermutations(const char* input)
{
	// let's get an output buffer
	int len = strlen(input);
	int totalOptions = 0;
	char* output = new char[len + 1];
	strcpy_s(output, (len + 1) * sizeof(char), input);
	// and then print the permutations
	StringPermutate::printOption(output, 0, len, &totalOptions);
	cout << "total permutations = " << totalOptions << "\n";
}