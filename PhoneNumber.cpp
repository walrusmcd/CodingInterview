#include <iostream>

using namespace std;

// use a dictionary for our options
const char* numberMap[] = {
	"0",
	"1",
	"2abc",
	"3def",
	"4ghi",
	"5jkl",
	"6mno",
	"7pqr",
	"8tuv",
	"9wxyz"
};

void printOption(char* option, int s, int len, int * totalOptions)
{
	// are we done?
	if (s == len) {
		// print it, we hit the end
		cout << option << "\n";
		*totalOptions += 1;
		return;
	}
	// convert our digit to an index
	int num = (int)(option[s] - '0');
	// grab the options for that digit
	const char* digitMap = numberMap[num];
	for (const char* p = digitMap; *p != '\0'; ++p) {
		// take this permutation
		option[s] = *p;
		// permtuate the rest
		printOption(option, s + 1, len, totalOptions);
	}
	// fix the string at the end
	option[s] = digitMap[0];
	return;
}

void printOptions(const char* phoneNumber)
{
	// let's get an output buffer
	int len = strlen(phoneNumber);
	char* output = new char[len+1];
	strcpy_s(output, (len+1) * sizeof(char), phoneNumber);
	// start at the beginning
	int totalOptions = 0;
	printOption(output, 0, len, &totalOptions);
	cout << "totalOptions = " << totalOptions << "\n";
	delete output; output = nullptr;
}

