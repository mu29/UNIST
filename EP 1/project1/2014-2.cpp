#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;
//-------------------------------------------------------------------------
// EP1 base-k converter by 20141566 InJung Chung
//-------------------------------------------------------------------------

// converts integer to character, also character to integer
int convert(char a);
char convert(int a);
void bplus(int *output, int k, int base);

int main() {
	//initialize variables
	int num1_base, num2_base, count;
	string again;
	do {
		// initialize count to 1
		count = 1;
		// initialize all output array to 0
		int output[128] = { 0, };
		// declare input array 4 
		string input[4];
		cout << "Provide k, number and j" << endl;
		// get line for array
		getline(cin, input[0]);
		// input 0 is received value
		// input 1 is base k
		// input 2 is number
		// input 3 is base j
		for (int i = 0; i < input[0].size(); i++) {
			// seperate each unit by blank
			if (input[0][i] == ' ') {
				count += 1;
				continue;
			}
			input[count] += input[0][i];
		}
		// error handling
		if (atoi(input[1].c_str()) < 2 || atoi(input[3].c_str()) < 2)
			cout << "*The system cannot handle a base < 1" << endl;
		else if (atoi(input[1].c_str()) > 16 || atoi(input[3].c_str()) > 16)
			cout << "*The system cannot handle a base > 16" << endl;
		else if (count <= 3)
		{
			bool is_minus = false;
			bool flag2 = true;
			for (int k = 0; k < input[2].size(); k++)
			{
				// check whether number is minus or not
				if (input[2][k] == '-')
					is_minus = true;
				// check input number if it contains base-j number
				if (convert(input[2][k]) >= atoi(input[1].c_str()))
					flag2 = false;
			}
			if (flag2 == false)
				cout << "*Your input is not in the given base" << endl;
			else
			{
				// converting base by add one by one
				for (int i = input[2].size() - 1; i >= 0; i--) {
					for (int j = 0; j < convert(input[2][i]) * (int)pow((double)atoi(input[1].c_str()), (double)(input[2].size() - 1 - i)); j++) {
						bplus(output, 0, atoi(input[3].c_str()));
					}
				}
				
				// print output
				cout << "Your output is ";
				if (is_minus)
					cout << "-";
				// ignore output array 0 that has no meaning
				bool flag = false;
				for (int i = 128; i > 0; i--) {
					if (output[i-1] != 0)
						flag = true;
					if (flag)
						cout << convert(output[i-1]);
				}
				cout << " in base-" << input[3] << endl;
				// ask retry
				cout << "Again? (-1 to quit or 1 to test again):" << endl;
				getline(cin, again);
			}
		}
		else 
		{
			cout << "Please enter only 3 values" << endl;
		}
	} while(again != "-1");
	cout << "Bye" << endl;
	return 0;
}

int convert(char a) {
	// ascii code table
	int list[16] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102 };
	for (int i = 0; i < 16; i++) {
		if (list[i] == a)
			return i;
	}
	return 0;
}

char convert(int a) {
	// ascii code table
	int list[16] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102 };
	return list[a];
}

void bplus(int *output, int k, int base) {
	// if number which is now calculating in cipher is equal to base, set number as zero and shift cipher
	if (output[k] == base - 1) {
		output[k] = 0;
		bplus(output, k+1, base);
	}
	else
		output[k]++;
}
