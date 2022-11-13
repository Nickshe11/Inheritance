#include <iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	std::ofstream fout; //Создаем поток
	fout.open("File.txt", std::ios::app); //Открываем поток
	//std::ios::app - append, не переписывать файлб а дописывать в файл
	// Пишем в поток
	fout << "Hello Files!" << endl;
	fout.close(); // Закрываем поток

	system("notepad File.txt"); //Функция system() запускает любую программу, к которой есть path в windows
#endif // WRITE_TO_FILE

	ifstream fin("File.txt");
	if (fin.is_open())
	{
		//Будем читать файл
		const int SIZE = 256; // Размер буфера может быть побольше, если текст в файле будет много текста
		char buffer[SIZE] = {};
		cout << typeid(fin.tellg()).name() << endl;
		while (!fin.eof())//eof - enfd of file (положение курсора на -1 - это конец файла)
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