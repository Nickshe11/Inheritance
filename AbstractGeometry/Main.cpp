#include<iostream>
#include<Windows.h>//���������� ��� ��������������� ������ �������
using namespace std;

enum Color// enum (enumeration) - ���������������� ��� ������, ����� ������������� ��������
// � ������� ������� color - ����� ������� ������
{
	console_default = 0x07,
	console_blue = 0x99,
	console_green = 0xAA,
	console_red = 0xCC,
	console_yellow = 0xEE
};


class Shape
{
protected: //���� protected �������� ������ ������ ������ � ������ �������� �������
	Color color;
public:
	Shape(Color color) :color(color) {}
	virtual ~Shape () {}
	virtual double area()const = 0;
	virtual double perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "������� ������: " << area() << endl;
		cout << "�������� ������: " << perimeter() << endl;
		draw();
	}
};

class Square : public Shape
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side < 5)side = 5;
		if (side > 20)side = 20;
		this->side = side;
	}
	//Constructors:
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	}
	~Square() {}
	double area()const override
	{
		return side * side;
	}
	double perimeter()const override
	{
		return side * 4;
	}
	void draw()const override
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//�������� ���� �������
		SetConsoleTextAttribute(hConsole, color);
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{

				cout << "* ";
			}
		cout << endl;
		}
	}
	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "����� �������: " << side << endl;
		Shape::info();
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Square square (8, Color::console_red);
	square.info();

}