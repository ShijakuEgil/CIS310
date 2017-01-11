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
using namespace std;

int convertToBinary(int i)
{
	
	int r;
	int q = i;
	stack<int> binNr;
	while (q > 0)
	{
		r = q % 2;
		binNr.push(r);
		q = q / 2;
	}
	
}
int convertToHex(int i)
{

}
int convertToBCD(int i)
{

}

int main()
{
	cout << "Decimal" << setw(5) << "Binary" << setw(5) 
		<< "Hexadecimal" << setw(5) << "BCD" << endl;

	for (int i = 0; i <= 255; i++)
	{
		cout << i << setw(5) << convertToBinary(i) << setw(5) 
			<< convertToHex(i) << setw(5) << convertToBCD(i) << endl;
	}
	return 0;
}