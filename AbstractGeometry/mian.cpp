#define _USE_MATH_DEFINES
//#define RED RGB(0,0,0)
#include<Windows.h>
#include<iostream>
using namespace std;

//#define HOM_W
namespace Geometry
{

	enum limits
	{
		MIN_SIZE = 50,
		MAX_SIZE = 500,
		MIN_LINE_WIDTH = 1,
		MAX_LINE_WIDTH = 30,
		MIN_START_X = 100,
		MAX_START_X = 1000,
		MIN_START_Y = 100,
		MAX_STZRT_Y = 700
	};

	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x00FFFF,
		white = 0x00FFFFFF
	};

#define SHAPE_TAKE_PARAMETERS int start_x, int stast_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, stast_y, line_width, color

	class Shape
	{
	protected:

		int start_x;
		int start_y;
		int line_width;
		Color color;

	public:

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}

		virtual ~Shape() {}

		int get_start_x()const
		{
			return start_x;
		}

		int get_start_y()const
		{
			return start_y;
		}

		int get_line_width()const
		{
			return line_width;
		}

		void set_start_x(int start_x)
		{
			if (start_x < limits::MIN_START_X)start_x = limits::MIN_START_X;
			if (start_y < limits::MIN_START_X)start_x = limits::MIN_START_X;
			this->start_x = start_x;
		}

		void set_start_y(int start_y)
		{
			if (start_y < limits::MIN_START_Y)start_y = limits::MIN_START_Y;
			if (start_y < limits::MIN_START_Y)start_y = limits::MIN_START_Y;
			this->start_y = start_y;
		}

		void set_line_width(int line_width)
		{
			if (line_width < limits::MIN_LINE_WIDTH)line_width = limits::MIN_LINE_WIDTH;
			if (line_width < limits::MIN_LINE_WIDTH)line_width = limits::MIN_LINE_WIDTH;
			this->line_width = line_width;
		}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual	void draw()const = 0;

		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~Square() {}

		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < limits::MIN_SIZE)side = limits::MIN_SIZE;
			if (side > limits::MIN_SIZE)side = limits::MAX_SIZE;
			this->side = side;
		}

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
			cout << "Длина стороны: " << side << endl;
			Shape::info();
		}
	};

	//------------------------------------------------------------------------------------------//

	class Rectangle :public Shape
	{
		double length;
		double width;
	public:
		Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_length(length);
		}

		~Rectangle() {}

		double get_length()const
		{
			return length;
		}
		double get_width()const
		{
			return width;
		}
		void set_length(double length)
		{
			if (length < limits::MIN_SIZE)length = limits::MIN_SIZE;
			if (length > limits::MAX_SIZE)length = limits::MAX_SIZE;
			this->length = length;
		}
		void set_width(double width)
		{
			if (width < limits::MIN_SIZE)width = limits::MIN_SIZE;
			if (width > limits::MAX_SIZE)width = limits::MAX_SIZE;
			this->width = width;
		}

		double get_area()const override
		{
			return length * width;
		}

		double get_perimeter()const override
		{
			return (length + width) * 2;
		}

		void draw()const override
		{
			/*
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < length; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			*/

			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина прямоугольника: " << length << endl;
			cout << "Ширина прямоугольника: " << width << endl;
			Shape::info();
		}
	};

	//------------------------------------------------------------------------------------------//

#ifdef HOM_W



	class Circle :public Shape
	{
		double radius;
	public:

		Circle(double radius)
		{
			set_radius(radius);
		}

		~Circle() {};

		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius < 5)radius = 5;
			if (radius > 10)radius = 10;
			this->radius = radius;
		}

		double get_area()const override
		{
			return radius * radius * 3.14;
		}

		double get_perimeter()const override
		{
			return 2 * 3.14 * radius;
		}

		void draw()const override
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			HWND handle = GetConsoleWindow();
			HDC hdc = GetDC(handle);

			//создаём перо (контур)
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); //сплошная линия, толщиной 2 пикселя, цвет - синий
			//создаём кисть (заливка)
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));//сплошной черный
			SelectObject(hdc, hPen);// указываем перо
			SelectObject(hdc, hBrush);//указываем кисть
			//рисуем эллипс
			Ellipse(hdc, 350, 350, 500, 500);

			DeleteObject(handle);
			DeleteObject(hPen);

			ReleaseDC(handle, hdc);

			/////////////////////////////////////////////////////////////////////////////////////////////////////
			/*
			for (int y = 0; y < 2 * radius + 1; y++)
			{
				for (int x = 0; x < 2 * radius + 1; x++)
				{
					if ((int)hypot(abs(radius - x), abs(radius - y)) == radius)
					{
						cout << "*";
					}
					else {
						cout << " ";
					}
				}
				cout << "\n";
			}

			cout << "\n";
			*/
			///////////////////////////////////////////////////////////////////////////////////////////////////
			/*
			double y1, y2;
			for (int i = 1; i <= 2 * radius; i++)
			{
				for (int j = 1; j <= 2 * radius; j++)
				{
					y1 = radius + sqrt(radius * radius - pow(radius - j, 2));
					y2 = radius - sqrt(radius * radius - pow(radius - j, 2));
					if (i > y2 && i < y1) std::cout << "**";
					else std::cout << "  ";
				}
				std::cout << std::endl;
			}
			*/
		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << radius << endl;
			Shape::info();
		}
	};

	//------------------------------------------------------------------------------------------//

	class Triangle :public Shape
	{
		double side_l;
		double side_r;
		double base;
		double height;
	public:
		Triangle(double side_l, double side_r, double base, double height)
		{
			set_side_l(side_l);
			set_side_r(side_r);
			set_base(base);
			set_height(height);
		}
		~Triangle() {};

		double get_side_l()const
		{
			return side_l;
		}

		double get_side_r()const
		{
			return side_r;
		}

		double get_base()const
		{
			return base;
		}

		double get_height()const
		{
			return height;
		}

		void set_side_l(double side_l)
		{
			if (side_l < 5)side_l = 5;
			if (side_l > 15)side_l = 15;
			this->side_l = side_l;
		}

		void set_side_r(double side_r)
		{
			if (side_r < 5)side_r = 5;
			if (side_r > 15)side_r = 15;
			this->side_r = side_r;
		}

		void set_base(double base)
		{
			if (base < 5)base = 5;
			if (base > 15)base = 15;
			this->base = base;
		}

		void set_height(double height)
		{
			if (height < 5)height = 5;
			if (height > 20)height = 20;
			this->height = height;
		}

		double get_area()const override
		{
			return 0.5 * base * height;
		}
		double get_perimeter()const override
		{
			return side_l + side_r + base;
		}
		void draw()const override
		{

			for (int i = 1; i <= height; ++i)
			{
				for (int j = height; j > i; --j)

					putchar(' ');

				for (int j = 1; j < 2 * i; ++j)

					putchar('*');
				putchar('\n');
			}

		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина сторон труегольника: " << side_l << side_r << base << endl;
			cout << "Высота треугольника: " << height << endl;
			Shape::info();
		}
	};
#endif // HOM_W

	class Circle : public Shape
	{
		double radius;

	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}

		~Circle() {};

		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius < limits::MIN_SIZE)radius = limits::MIN_SIZE;
			if (radius > limits::MAX_SIZE)radius = limits::MAX_SIZE;
			this->radius = radius;
		}

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
			//--------------------------------------------------//

			::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			//--------------------------------------------------//
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
	};
}


void main()
{
	setlocale(LC_ALL, "");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	Geometry::Square square(8, 7, 7, 5, Geometry::Color::blue);
	/*
	cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрат: " << square.get_perimeter() << endl;
	square.draw();
	*/
	square.info();

	Geometry::Rectangle rect(150, 77, 200, 100, 5, Geometry::Color::red);
	rect.info();

	Geometry::Circle rad(200, 200, 100, 5, Geometry::Color::green);
	rad.info();

	//Geometry::Triangle tri(3, 7, 9, 5);
	//tri.info();

}