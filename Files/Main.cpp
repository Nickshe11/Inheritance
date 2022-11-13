#include <iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	std::ofstream fout; //������� �����
	fout.open("File.txt", std::ios::app); //��������� �����
	//std::ios::app - append, �� ������������ ����� � ���������� � ����
	// ����� � �����
	fout << "Hello Files!" << endl;
	fout.close(); // ��������� �����

	system("notepad File.txt"); //������� system() ��������� ����� ���������, � ������� ���� path � windows
#endif // WRITE_TO_FILE

	ifstream fin("File.txt");
	if (fin.is_open())
	{
		//����� ������ ����
		const int SIZE = 256; // ������ ������ ����� ���� ��������, ���� ����� � ����� ����� ����� ������
		char buffer[SIZE] = {};
		cout << typeid(fin.tellg()).name() << endl;
		while (!fin.eof())//eof - enfd of file (��������� ������� �� -1 - ��� ����� �����)
		{
			//fin >> buffer;
			cout << fin.tellg() << "\t";
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		cout << fin.tellg() << "\n";
	fin.close();
	}
	else
	{
		std::cerr << "Error: file not founf" << endl;
	}

}