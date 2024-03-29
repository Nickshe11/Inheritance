﻿#define _USE_MATH_DEFINES
#include<iostream>
#include<ctime>
#include<Windows.h>//библиотека для манипулирования цыетом консоли
using namespace std;

#define RAND rand()%500
#define COLOR RGB(rand(), rand(), rand())

namespace Geometry
{
	enum Color// enum (enumeration) - пользовательский тип данных, набор целочисленных констант
	// в консоли команда color - вывод номеров цветов
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		white = 0x00FFFFFF,
		grey = 0x00AAAAAA,
		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE
	};

	class Shape
	{
	protected: //поля protected доступны внутри нашего класса и внутри дочерних классов
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 800)start_x = 800;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 500)start_y = 500;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 500)line_width = 500;
			this->line_width = line_width;
		}
		Shape(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			//draw();
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
		Square(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Shape(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~Square() {}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//Получаем окно консоли
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{

					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << side << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width < 30)width = 30;
			if (width > 300)width = 300;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 20)length = 20;
			if (length > 200)length = 200;
			this->length = length;
		}
		//Constructors
		Rectangle(double width, double length, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Shape(start_x, start_y, line_width, color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double get_area()const override
		{
			return width * length;
		}
		double get_perimeter()const override
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < length; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);*/
			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();
			//2) Получаем контекст устройства для окна консоли:
			HDC hdc = GetDC(hwnd);	//это то, на чем мы будем рисовать

			//3) Создаем карандаш - это то, чем мы будем рисорвать (карандаш рисует линии):
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			//4) Создаем кисть. Кисть рисует заливку в замкнутой фигуре
			HBRUSH hBrush = CreateSolidBrush(color);
			//5) Выбираем чем, и на чем мы будем рисорвать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольник:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);

			//Удаляем карандаш:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			//Освобождаем контекст устройства:
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << width << endl;
			cout << "Длина: " << length << endl;
			Shape::info();
		}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius < 20)radius == 20;
			if (radius > 220)radius = 220;
			this->radius = radius;
		}
		Circle(double radius, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI * radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + radius * 2, start_y + radius * 2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Radius: " << radius << endl;
			Shape::info();
		}

	};
	class Triangle :public Shape
	{
	public:
		Triangle(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Shape(start_x, start_y, line_width, color) {}
		virtual double get_height()const = 0;
		void info()const
		{
			cout << "Height:" << get_height() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 20)side = 20;
			if (side > 200)side = 200;
			this->side = side;
		}
		EquilateralTriangle(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		double get_height()const override
		{
			return 2 * get_area() / side;
		}
		double get_area()const override
		{
			return side * side * sqrt(3) / 4;
		}
		double get_perimeter()const override
		{
			return side * 3;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, vert, 3);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Side: " << side << endl;
			cout << "Height: " << get_height() << endl;
			Triangle::info();
			while (true)
			{
				draw();
			}
		}
	};

	class RightTriangle :public Triangle
	{
		double height;
		double base;
	public:
		double get_height()const
		{
			return height;
		}
		double get_base()const
		{
			return base;
		}
		void set_height(double height)
		{
			if (height < 20)height = 20;
			if (height > 200)height = 200;
			this->height = height;
		}
		void set_base(double base)
		{
			if (base < 20)base = 20;
			if (base > 200)base = 200;
			this->base = base;
		}
		RightTriangle(double height, double base, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Triangle(start_x, start_y, line_width, color)
		{
			set_height(height);
			set_base(base);
		}
		~RightTriangle() {}

		double get_area()const override
		{
			return height * base / 2;
		}
		double get_perimeter()const override
		{
			return height + base + (sqrt(height * height + base * base));
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[] =
			{
				{start_x, start_y + height},
				{start_x + base, start_y + height},
				{start_x , start_y }
			};
			::Polygon(hdc, vert, 3);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Высота: " << height << endl;
			cout << "Основание: " << base << endl;
			Triangle::info();
		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double side;
		double base;
	public:
		double get_side()const
		{
			return side;
		}
		double get_base()const
		{
			return base;
		}
		void set_side(double side)
		{
			if (side < 20)side = 20;
			if (side > 200)side = 200;
			this->side = side;
		}
		void set_base(double base)
		{
			if (base < 20)base = 20;
			if (base > 200)base = 200;
			this->base = base;
		}
		IsoscelesTriangle(double side, double base, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
			set_base(base);
		}
		~IsoscelesTriangle() {}
		double get_height()const override
		{
			return sqrt(side * side - base / base / 4);
		}
		double get_area()const override
		{
			return base * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return side * 2 + base;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[] =
			{
				{start_x, start_y + get_height()},
				{start_x + base, start_y + get_height()},
				{start_x + base / 2, start_y }
			};
			::Polygon(hdc, vert, 3);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона: " << side << endl;
			cout << "Основание: " << base << endl;
			cout << "Height: " << get_height() << endl;
			Triangle::info();
		}
	};
	//class Circle : public Shape
	//{
	//	double radius;
	//public:
	//	double get_radius()const
	//	{
	//		return radius;
	//	}
	//	void set_radius(double radius)
	//	{
	//		if (radius < 5)radius = 5;
	//		if (radius > 30) radius = 30;
	//		this->radius = radius;
	//	}

	//	Circle(double radius, Color color) : Shape(color)
	//	{
	//		set_radius(radius);
	//	}
	//	~Circle() {};
	//	double area()const override
	//	{
	//		return 3.14 * radius * radius;
	//	}
	//	double get_perimeter() const override
	//	{
	//		return 2 * 3.14 * radius;
	//	}

	//	void draw()const
	//	{
	//		HWND hwnd = GetConsoleWindow();
	//		HDC hdc = GetDC(hwnd);
	//		HPEN hPen = CreatePen(PS_SOLID, 5, color);
	//		HBRUSH hBrush = CreateSolidBrush(color);
	//		SelectObject(hdc, hPen);
	//		SelectObject(hdc, hBrush);
	//		::Ellipse(hdc, 100, 100, 300, 300);
	//		DeleteObject(hPen);
	//		ReleaseDC(hwnd, hdc);

	//	}
	//	void info()const override
	//	{
	//		cout << typeid(*this).name() << endl;
	//		cout << "Радиус: " << radius << endl;
	//		Shape::info();
	//	}
	//};
	//class Triangle :public Shape
	//{
	//	double height;
	//	double base;
	//public:
	//	double get_height() const
	//	{
	//		return height;
	//	}
	//	double get_base()const
	//	{
	//		return base;
	//	}

	//	void set_height(double height)
	//	{
	//		if (height < 5)height = 5;
	//		if (height > 30)height = 30;
	//		this->height = height;
	//	}
	//	void set_base(double base)
	//	{
	//		if (base < 5)base = 5;
	//		if (base > 30)base = 30;
	//		this->base = base;
	//	}
	//	
	//	Triangle(double height, double base, Color color) : Shape(color)
	//	{
	//		set_height(height);
	//		set_base(base);
	//	}
	//	~Triangle() {};
	//	double area()const override
	//	{
	//		return base * height / 2;
	//	}
	//	double get_perimeter()const override
	//	{
	//		return base + 2 * (sqrt(height * height + (base / 2) * (base / 2)));// Для равностороннего треугольника
	//	}
	//	void draw()const
	//	{
	//		
	//		
	//	}
	//	void info()const override
	//	{
	//		cout << typeid(*this).name() << endl;
	//		cout << "Высота: " << height << endl;
	//		cout << "Основание: " << base << endl;
	//		Shape::info();
	//	}
	//}; 
	Shape* Factory(int type)
	{
		switch (type)
		{
		//case 1: return new Square(rand(), rand(), rand(), rand(), (Color)rand()); break;
		case 0: return new Rectangle(RAND, rand()%500, rand() % 500, RAND, RAND, (Color)COLOR); break;
		case 1: return new Circle(RAND, rand() % 500, rand() % 500, RAND, (Color)COLOR); break;
		case 2: return new EquilateralTriangle(RAND, rand() % 500, rand() % 500, RAND, (Color)COLOR); break;
		}
	}
}


void main()
{
	setlocale(LC_ALL, "");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	srand(time(NULL));
	//Geometry::Square square(8, 100, 100, 11, Geometry::Color::console_red);
	//square.info();
	//Geometry::Rectangle rect(150, 70, 300, 100, 11, Geometry::Color::grey);
	//rect.info();
	///*Geometry::Circle round(5, Geometry::Color::console_green);
	//round.info();*/
	//Geometry::Circle circle(100, 700, 100, 11, Geometry::Color::yellow);
	//circle.info();
	///*Geometry::EquilateralTriangle e_try(170, 350, 200, 8, Geometry::Color::green);
	//e_try.info();*/
	///*Geometry::RightTriangle r_try(170, 170, 350, 200, 8, Geometry::Color::green);
	//r_try.info();*/
	//Geometry::IsoscelesTriangle i_try(170, 170, 350, 200, 8, Geometry::Color::green);
	//i_try.info();
	const int n = 5;
	Geometry::Shape* shape[n];
	for (int i = 0; i < n; i++)
	{
		shape[i] = Geometry::Factory(rand() % 3);
	}
	for (int i = 0; i < n; i++)
	{
		shape[i]->draw();
		Sleep(100);
	}
	for (int i = 0; i < n; i++)
	{
		delete shape[i];
	}

}