/*
Egil Shijaku
Program 4 CIS 310
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<deque>
using namespace std;
const char HEX[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
'B', 'C', 'D', 'E', 'F', '+', '-', '*', '/', '$' };

class FullAdder
{
	int quot = 0;
	int operand = -1;
	string lineIn;
	deque<int> reg1;
	deque<int> reg2;
	deque<int> binSolution;
	deque<int> twosComplement;
	char convertToHex(int bin[4])
	{
		int hex = 0;
		int power = 3;
		for (int i = 0; i < 4; i++)
		{
			hex = hex + (bin[i] * pow(2, power));
			power--;
		}
		return HEX[hex];
	}
	int getDec(deque<int> bin)
	{
		int dec = 0;
		int power = bin.size() - 1;
		for (int x : bin)
		{
			dec =  dec + (x * pow(2, power));
			power--;
		}
		return dec;
	}
public:
	FullAdder(string equation)
	{
		lineIn = equation;
		for (char x : lineIn)
		{
			int id = getHexNr(x);
			if (id >= 0)
			{
				if (id > 15) // if id > 15 it mean that the current input is an operand 
				{
					operand = id;
				}
				if (id <= 15)// hex number
				{
					loadRegs(id);
				}
			}
		}
	}
	int getHexNr(char x)
	{
		/*
		Description:	Converts the string input rapresentation of the hex
		into a number corresponding to the array id
		*/
		for (int i = 0; i < 21; i++)
		{
			if (x == HEX[i])
			{
				return i;
			}
		}
		return -1;
	}
	void loadRegs(int hex)
	{
		int bin[4];
		for (int i = 3; i >= 0; i--)
		{
			bin[i] = hex % 2;
			hex = hex / 2;
			//cout << bin[i] << hex << " "; 
			//cout << operand << endl;
		}
		if (operand == -1) // means that operand has not passed yet
						   //therefore loads left side register(reg1)
		{
			for (int i = 0; i < 4; i++)
			{
				reg1.push_back(bin[i]);
			}
		}
		if (operand != -1)//means operand is loaded so right side of 
						  //operations is loaded(reg2)
		{
			for (int i = 0; i < 4; i++)
			{
				reg2.push_back(bin[i]);
			}
		}
	}
	void addition(deque<int> reg1, deque<int> reg2, int i = 0)
	{
		int carry = 0;
		int x;
		int y;
		int n = 1;
		while (n <= reg1.size() || n <= reg2.size())
		{
			if (n > reg1.size())
			{
				x = 0;
			}
			else {
				x = reg1[reg1.size() - n];
			}
			if (n > reg2.size())
			{
				y = 0;
			}
			else
			{
				y = reg2[reg2.size() - n];
			}
			if (i == 0)
			{
				binSolution.push_front(x ^ y ^ carry);
				carry = (x & y) | (x & carry) | (y & carry);
			}
			else if (i == 1)
			{
				twosComplement.push_front(x ^ y ^ carry);
				carry = (x & y) | (x & carry) | (y & carry);
			}
			n++;
		}
		if (carry == 1 && i == 0)
		{
			binSolution.push_front(carry);
		}
		if (carry == 1 && i == 1)
		{
			twosComplement.push_front(carry);
		}
	}
	void subtraction(deque<int> reg1, deque<int> reg2)
	{
		deque<int> temp = { 1 };
		int size = reg1.size() - reg2.size();
		for (int i = 0; i < size; i++)
		{
			reg2.push_front(0);
		}
		for (int i = 0; i < reg2.size(); i++)
		{
			if (reg2[i] == 0)
				reg2[i] = 1;
			else
				reg2[i] = 0;
		}
		addition(reg2, temp, 1);
		addition(reg1, twosComplement);
	}
	void mul(deque<int> reg1, deque<int> reg2)
	{
		int dec = getDec(reg2);
		deque<int> temp;
		while (dec > 0)
		{
			addition(temp, reg1);
			temp = binSolution;
			binSolution.clear();
			dec--;
		}
		binSolution = temp;
	}
	void div(deque<int> reg1, deque<int> reg2)
	{
		deque<int> temp = reg1;
		
		while (getDec(temp) > getDec(reg2))
		{
			subtraction(temp, reg2);
			temp = binSolution;
			binSolution.clear();
			quot++;
		}
		binSolution = temp;

	}
	void findResult()
	{
		/*
		Description:	finnds which operand was loaded and performs that operation
		*/
		if (operand == 16)
			addition(reg1,reg2);
		else if (operand == 17)
			subtraction(reg1, reg2);
		else if (operand == 18)
			mul(reg1, reg2);
		else if (operand == 19)
			div(reg1, reg2);
		//else if (operand == 20)
			//power(reg1, reg2);
	}
	void print()
	{
		cout << lineIn ;
		if (operand == 19)
		{
			deque<char> qHex;
			
			if (quot > 15)
			{
				cout << "quotionet: ";
				while (quot >= 0)
				{
					qHex.push_front(HEX[quot % 16]);
					quot = quot / 16;
				}
				for (auto x : qHex) {
					cout << x;
				}
				cout << " Remainder: ";
			}
			else
			{
				cout << "quotionet: " << HEX[quot] << " Remainder: ";
			}
		}
		char hex;
		int i = 0;
		int bin[4];
		for (int x : binSolution)
		{
			bin[i] = x;
			if (i == 3)
			{
				hex = convertToHex(bin);
				i = 0;
				cout << hex;
			}
			else
				i++;
		}
		cout << endl;

	}
};

int main()
{
	vector<FullAdder> equations;
	string line;
	ifstream input("input.txt");
	if (input.is_open())
	{
		while (getline(input, line))
		{
			FullAdder newOperand(line);
			equations.push_back(newOperand);
		}
		input.close();
	}
	else
		cout << "unable to open file" << endl;

	for (auto x : equations)
	{
		x.findResult();
		x.print();
	}
	return 0;
}
