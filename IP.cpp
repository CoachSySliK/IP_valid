#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool point(string address)
{
	int counter = 0;
	for (int i = 1; i < address.length(); i++)
	{
		if (address[i] == '.' && address[i] != address[i - 1])
			++counter;
		if (address[i] == '0' && address[i] == address[i - 1])
		{
			cout << "Invalid (00)\n";
			return false;
		}
	}
	if (counter == 3)
		return true;
	cout << "Invalid (point)\n";
	return false;
}

bool number(string address)
{
	for (int i = 0; i < address.length(); i++)
	{
		if ((address[i] >= '0' && address[i] <= '9') || address[i] == '.')
		{
			continue;
		}
		else
		{
			cout << "Invalid (number)\n";
			return false;
		}
	}
	return true;
}

bool oktet(string address, int *oktet, const int C)
{
	for (int i = 1; i <= C; i++)
	{
		string okt;
		for (int j = 0; j < address.length(); j++)
		{
			if (address[address.length() - j - 1] != '.')
			{	
				okt += address[address.length() - j - 1];
				oktet[C - i] += (address[address.length() - j - 1] - 48) * pow(10, j);
			}
			else
			{
				address.erase(address.length() - j - 1);
				break;
			}
			//cout << okt << endl;
			if (okt.length() > 1 && okt[1] == '0')
			{
				cout << "Invalid (00)\n";
				return false;
			}
		}
	}
	return true;
}

bool value(int *oktet, const int C)
{
	for (int i = 0; i < C; i++)
	{
		if (oktet[i] > 255)
		{
			//cout << oktet[i] << endl;
			cout << "Invalid (value)\n";
			return false;
		}
	}
	return true;
}

int main(void)
{
	do
	{
		string address;
		bool valid = false;
		const int C = 4;
		int oktets[C] = {0};
		int *ptroktets = oktets;
		do
		{
			cout << "Input your IP-address: ";
			cin >> address;

			valid = number(address);
			if (!valid)
				continue;

			valid = point(address);
			if (!valid)
				continue;

			valid = oktet(address, ptroktets, C);
			if (!valid)
				continue;
				
			/*for (int i = 0; i < C; i++)
				cout << oktets[i] << endl;*/

			valid = value(ptroktets, C);
			if (!valid)
				continue;
				
		} while (!valid);
		//cout << address << endl;
		cout << "Valid" << endl;
	} while (true);
	return 0;
}