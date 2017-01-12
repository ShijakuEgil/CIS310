/*
Egil Shijaku
CIS 310
Program 0 (Number Conversion)
Prof. David Yoon
*/
#include<iostream>
#include<stack>
#include<iomanip>
#include<stack>
#include<string>
using namespace std;

string hexAlph[]={"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};

string convertToBinary(int i)
{
	int b = i;
	int r;
	int q;
	string nr;

	if (b == 0)
		return "0";
	while (b > 0)
	{
		r = b % 2;
		nr.insert(0, to_string(r));
		q = b / 2;
		b = q;
	}
	return nr;
}

string convertToHex(int i)
{
	int b = i;
	int r;
	int q;
	string nr;
	if (b == 0)
		return "0";
	while (b > 0)
	{
		r = b % 16;
		nr.insert(0,hexAlph[r]);
		q = b / 16;
		b = q;
	}
	return nr;
}
int convertToBCD(int i)
{
	return 0;
}

int main()
{
	cout << "Decimal" << setw(15) << "Binary" << setw(15) 
		<< "Hexadecimal" << setw(15) << "BCD" << endl;

	for (int i = 0; i < 256; i++)
	{
		cout << i << setw(15) << convertToBinary(i)<< setw(15) 
			<< convertToHex(i) << setw(15) << convertToBCD(i) << endl;
	}
	return 0;
}