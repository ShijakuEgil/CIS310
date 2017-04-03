/*
Egil Shijaku
Program 4 CIS 310
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stack>
#include<deque>
using namespace std;
const char HEX[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
					      'B', 'C', 'D', 'E', 'F', '+', '-', '*', '/', '$' };
class FullAdder
{
	string lineIn;
	vector<int> reg1;
	vector<int> reg2;
	deque<int> solution;
	deque<int> tempSolution;
	int operand = -1;
	int carry = 0;
	void add(int x, int y, string t)
	{
		int sum = x ^ y ^ carry;
		carry = (x & y) | (x & carry) | (y & carry);
		if(t == "add")
			solution.push_front(sum);
		if (t == "sub")
			tempSolution.push_front(sum);
	}
	char convertToHex(int bin[4])
	{
		int hex = 0;
		int power = 3;
		for (int i = 0; i < 4; i++)
		{
			hex = hex +(bin[i] * pow(2, power));
			power--;
		}
		return HEX[hex];
	}
public:
	FullAdder(string input)
	{
		for (auto x : input )
		{
			int id = getDigits(x); //gets number 
			if (id >= 0)
			{
				if (id > 15) // if id > 15 it mean that the current input is an operand 
				{
					operand = id;
				}
				if(id <= 15)// hex number
				{
					loadRegs(id);
				}
				lineIn.push_back(x);
			}
		}
	}

	int getDigits(char hex)
	{
		/*
		Description:	Converts the string input rapresentation of the hex 
						into a number corresponding to the array id
						*/
		for (int i = 0; i < 21; i++)
		{
			if (hex == HEX[i])
			{
				return i;
			}	
		}
		return -1;
	}
	void loadRegs(int hex)
	{
		/*
		Description:	loads the register that are going to perform operation in operand
						*/
		int i = 3;
		int bin[4];
		while (i > -1)
		{
			bin[i] = hex % 2;
			int quot= hex / 2;
			hex = quot;
			i--;
			if (hex == 0 && i > 0)
			{
				for (int j = i - 1; j > -1; j--)
				{
					bin[j] = 0;
				}
			}
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
	deque<int> twoComplement(vector<int> reg)
	{
		vector<int> temp;
		temp.push_back(1);
		vector<int> temp1;
		for (int i = 0; i < reg.size(); i++)
		{
			if (reg[i] == 0)
				temp1.push_back(1);
			if (reg[i] == 1)
				temp1.push_back(0);

		}
		addition(temp1, temp, "sub");
		return tempSolution;
	}
	void addition(vector<int> reg1, vector<int> reg2, string t)
	{
		/*
		Description:	 adds the two registers
						*/
		int x1;
		int x2;
		int n = 1;
		while (n <= reg1.size() || n <= reg2.size())
		{
			if (n > reg1.size() )
			{
				x1 = 0;
			}
			else {
				x1 = reg1[reg1.size() - n];
			}
			if (n > reg2.size() )
			{
				x2 = 0;
			}
			else
			{
				x2 = reg2[reg2.size() - n];
			}
			add(x1, x2, t);
			n++;
		}
	}
	void addition(vector<int> reg1, deque<int> reg2, string t)
	{
		/*
		Description:	 adds the two registers
		*/
		int x1;
		int x2;
		int n = 1;
		while (n <= reg1.size() || n <= reg2.size())
		{
			if (n > reg1.size())
			{
				x1 = 0;
			}
			else {
				x1 = reg1[reg1.size() - n];
			}
			if (n > reg2.size())
			{
				x2 = 0;
			}
			else
			{
				x2 = reg2[reg2.size() - n];
			}
			add(x1, x2, t);
			n++;
		}
	}
	void subtraction(vector<int> reg1, vector<int> reg2)
	{
		vector<int> temp;
		int size = reg1.size() - reg2.size();
		for (int i = 0; i < size; i++) {
			temp.push_back(0);
		}
		for (int x : reg2)
		{
			temp.push_back(x);
		}
		deque<int> reg21;
		reg21 = twoComplement(temp);
		addition(reg1, reg21, "add");
	}
	void mul(vector<int> reg1, vector<int> reg2)
	{
		int x = convertToDec(reg2);
		while (x != 0)
		{

		}
	}
	void div(vector<int> reg1, vector<int> reg2)
	{

	}
	void power(vector<int> reg1, vector<int> reg2)
	{

	}
	void print()
	{
		char hex;
		int i = 0;
		int bin[4];
		for (int x : solution)
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

	void findResult()
	{
		/*
		Description:	finnds which operand was loaded and performs that operation
		*/
		if (operand == 16)
			addition(reg1, reg2, "add");
		else if (operand == 17)
			subtraction(reg1, reg2);
		else if (operand == 18)
			mul(reg1, reg2);
		else if (operand == 19)
			div(reg1, reg2);
		else if (operand == 20)
			power(reg1, reg2);
	}
};

int main()
{
	//vector<FullAdder> operands;
	string line;
	ifstream input("input.txt");
	if (input.is_open())
	{
		while (getline(input, line))
		{
			cout << line;
			FullAdder newOperand(line);
			newOperand.findResult();
			newOperand.print();
		}
		input.close();
	}
	else
		cout << "unable to open file" << endl;

	return 0;
}