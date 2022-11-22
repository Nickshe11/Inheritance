#include<iostream>
#include<Windows.h>//библиотека для манипулирования цыетом консоли
using namespace std;

namespace Geometry
{
	enum Color// enum (enumeration) - пользовательский тип данных, набор целочисленных констант
// в консоли команда color - вывод номеров цветов
	{
		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE
	};


	class Shape
	{
	protected: //поля protected доступны внутри нашего класса и внутри дочерних классов
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual double area()const = 0;
		virtual double perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << area() << endl;
			cout << "Периметр фигуры: " << perimeter() << endl;
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
			if (width < 8)width = 8;
			if (width > 30)width = 30;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 3)length = 3;
			if (length > 20)length = 20;
			this->length = length;
		}
		//Constructors
		Rectangle(double width, double length, Color color) : Shape(color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double area()const override
		{
			return width * length;
		}
		double perimeter()const override
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
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			//4) Создаем кисть. Кисть рисует заливку в замкнутой фигуре
			HBRUSH hBrush = CreateSolidBrush(color);
			//5) Выбираем чем, и на чем мы будем рисорвать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольник:
			::Rectangle(hdc, 100, 100, 500, 300);

			//Удаляем карандаш:
			DeleteObject(hPen);

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
	class Circle : public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius < 5)radius = 5;
			if (radius > 30) radius = 30;
			this->radius = radius;
		}

		//Constructors
		Circle(double radius, Color color) : Shape(color)
		{
			set_radius(radius);
		}
		~Circle() {};
		double area()const override
		{
			return 3.14 * radius * radius;
		}
		double perimeter() const override
		{
			return 2 * 3.14 * radius;
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, 100, 100, 300, 300);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << radius << endl;
			Shape::info();
		}
	};
	class Triangle :public Shape
	{
		double height;
		double base;
	public:
		double get_height() const
		{
			return height;
		}
		double get_base()const
		{
			return base;
		}

		void set_height(double height)
		{
			if (height < 5)height = 5;
			if (height > 30)height = 30;
			this->height = height;
		}
		void set_base(double base)
		{
			if (base < 5)base = 5;
			if (base > 30)base = 30;
			this->base = base;
		}
		//Constructors
		Triangle(double height, double base, Color color) : Shape(color)
		{
			set_height(height);
			set_base(base);
		}
		~Triangle() {};
		double area()const override
		{
			return base * height / 2;
		}
		double perimeter()const override
		{
			return base + 2 * (sqrt(height * height + (base / 2) * (base / 2)));// Для равностороннего треугольника
		}
		void draw()const
		{
			
			/*HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			
			::Polygon();
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);*/

		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Высота: " << height << endl;
			cout << "Основание: " << base << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	/*Geometry::Square square(8, Geometry::Color::console_red);
	square.info();
	Geometry::Rectangle rect(15, 7, Geometry::Color::console_yellow);
	rect.info();*/
	Geometry::Circle round(5, Geometry::Color::console_green);
	round.info();
}