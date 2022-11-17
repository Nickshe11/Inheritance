#include <iostream>
#include<fstream>
#include<string>

using namespace std;

void main()
{
	setlocale(LC_ALL, "");

	ifstream fin("RAW.txt");
	int counter = 1;
	if (fin.is_open())
	{		
		while (!fin.eof())
		{			
			std::string buffer_ip{};
			std::string buffer_mac{};
			std::getline(fin, buffer_ip, ' ');
			std::getline(fin, buffer_mac);
			while (buffer_mac[0] == ' ')
			{
				for (int j = 0; j <= size(buffer_mac) - 1; j++)	buffer_mac[j] = buffer_mac[j + 1];
				buffer_mac.pop_back();
			}
			cout << buffer_mac << "\t" << buffer_ip << endl;

			std::ofstream fout_ready;
			fout_ready.open("READY.txt", std::ios::app);
			fout_ready << buffer_mac << "\t" << buffer_ip << endl;
			fout_ready.close();

			std::ofstream fout_dhcpd;
			fout_dhcpd.open("201.dhcpd", std::ios::app);
			fout_dhcpd << "host 201-" << counter << "\n" << "{\n\thardware ethernet\t" << buffer_mac << ";\n\tfixed-address\t\t" << buffer_ip << ";\n}\n\n";
			counter++;
		}
		fin.close();
	}
	else cout << "Error file not found";
}