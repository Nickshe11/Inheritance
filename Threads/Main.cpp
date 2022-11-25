#include <iostream>
#include <thread>
using namespace std;
using namespace std::chrono_literals;

bool finish = false;

void Plus()
{
	while (!finish)
	{
		cout << "+ ";
		std::this_thread::sleep_for(1s);
	}
}
void Minus()
{
	while (!finish)
	{
		std::this_thread::sleep_for(1s);
		cout << "- ";
	}
}

void main()
{
	setlocale(LC_ALL, "");
	//Plus();
	//Minus();
	std::thread plus_thread(Plus);
	std::thread minus_thread(Minus);

	cin.get();//����� get () ������� ������� Enter
	finish = true;

	//����� join() ������������� ����� � �������������� ��� � �������� �������
	// � ������ ����������� ������� main

	minus_thread.join();
	plus_thread.join();

}