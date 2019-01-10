#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX = 255;
const int MAX_MASK = 32;

struct Network
{
	int computers;
	string networkAddress;
	int mask;
	string minAddress;
	string maxAddress;
	string broadcast;
};

struct PowerOfTwo
{
	int value;
	int power;
};

vector<Network> networks;

int ipAddress [4] = { 12, 0, 0, 0 };


PowerOfTwo findClosestPowerOfTwo(int number)
{
	int value = 2;
	int power = 1;

	while (value <= number)
	{
		value *= 2;
		power++;
	}

	return { value, power };
}

void writeTitle()
{
	cout << "IP CALC FOR PSI FEL CVUT" << endl;
	cout << "========================" << endl << endl << endl;
	cout << "NETWORKS" << endl << endl;
	cout << "Enter network sizes one-by-one (escape character is 0):" << endl;
}

void readLoop()
{
	writeTitle();

	int networkSize = 0;

	while (true)
	{
		cin >> networkSize;

		if (networkSize != 0)
		{
			Network foo;
			foo.computers = networkSize;
			networks.push_back(foo);
		}
		else
		{
			break;
		}
	}
}

void add(int i, PowerOfTwo sizeOfNetwork, bool over)
{
	// mask
	networks.at(i).mask = MAX_MASK - sizeOfNetwork.power;
	
	// network address
	if (over)
	{
		int foo = (sizeOfNetwork.value / 256);

		while (ipAddress[2] % foo != 0)
		{
			ipAddress[2]++;
		}
	}
	networks.at(i).networkAddress = to_string(ipAddress[0]) + "." + to_string(ipAddress[1]) + "." + to_string(ipAddress[2]) + "." + to_string(ipAddress[3]);

	// minimum IP address for PC
	ipAddress[3]++;
	networks.at(i).minAddress = to_string(ipAddress[0]) + "." + to_string(ipAddress[1]) + "." + to_string(ipAddress[2]) + "." + to_string(ipAddress[3]);

	// maximum IP address for PC
	if (over)
	{
		ipAddress[2] += (sizeOfNetwork.value / 256) - 1;
		ipAddress[3] = 254;
	}
	else
	{
		ipAddress[3] += sizeOfNetwork.value - 3;
	}
	networks.at(i).maxAddress = to_string(ipAddress[0]) + "." + to_string(ipAddress[1]) + "." + to_string(ipAddress[2]) + "." + to_string(ipAddress[3]);
	

	// broadcast
	ipAddress[3]++;
	networks.at(i).broadcast = to_string(ipAddress[0]) + "." + to_string(ipAddress[1]) + "." + to_string(ipAddress[2]) + "." + to_string(ipAddress[3]);

	ipAddress[3]++;
}

void calculate()
{
	cout << endl << endl << "RESULTS" << endl << endl;
	cout << "PCs \tNetw Addr \tMask \tMin Addr \tMax Addr \tBroadcast" << endl;

	for (int i = 0; i < networks.size(); i++)
	{
		PowerOfTwo sizeOfNetwork = findClosestPowerOfTwo(networks.at(i).computers + 2);

		if (ipAddress[3] + sizeOfNetwork.value - 1 <= MAX)
		{
			add(i, sizeOfNetwork, false);
		}
		else
		{

			if (sizeOfNetwork.value < MAX) {
				ipAddress[2]++;
				ipAddress[3] = 0;
				add(i, sizeOfNetwork, false);
			}
			else if ( ipAddress[3] == 0)
			{
				add(i, sizeOfNetwork, true);
			}
			else
			{
				ipAddress[2]++;
				ipAddress[3] = 0;
				add(i, sizeOfNetwork, true);
			}
		}

		cout << networks.at(i).computers << "\t" << networks.at(i).networkAddress << "\t" << networks.at(i).mask << "\t" << networks.at(i).minAddress << "\t" << networks.at(i).maxAddress << "\t" << networks.at(i).broadcast << endl;
	}
}

int main()
{
	readLoop();
	calculate();
	system("PAUSE");
}