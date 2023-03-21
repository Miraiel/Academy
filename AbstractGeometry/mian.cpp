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
	//------------------------------------------------------------------------------------------//

	/*
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
	};*/

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

	class Square : public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
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

	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}

		virtual double get_height()const = 0;

		void info()const
		{
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};

	//------------------------------------------------------------------------------------------//

	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}

		~EquilateralTriangle() {}

		double get_side()const
		{
			return side;
		}

		void set_side(double side)
		{
			if (side < limits::MIN_SIZE)side = limits::MIN_SIZE;
			if (side > limits::MAX_SIZE)side = limits::MAX_SIZE;
			this->side = side;
		}

		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}

		double get_area()const
		{
			return side * get_height() / 2;
		}

		double get_perimeter()const
		{
			return side * 3;
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hpen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hpen);
			SelectObject(hdc, hBrush);

			POINT vertex[] =
			{
				{start_x, start_y + side},
				{start_x + side,start_y + side},
				{start_x + side / 2,start_y + side - get_height()}
			};

			::Polygon(hdc, vertex, 3);

			DeleteObject(hpen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны " << side << endl;
			Triangle::info();
		}

	};

	class IsoscelesTriangle :public Triangle
	{
		double side;
	
	public:
		IsoscelesTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}

		~IsoscelesTriangle() {}

		double get_side()const
		{
			return side;
		}

		void set_side(double side)
		{
			if (side < limits::MIN_SIZE)side = limits::MIN_SIZE;
			if (side > limits::MAX_SIZE)side = limits::MAX_SIZE;
			this->side = side;
		}

		double get_base()const
		{
			return sqrt(2 * pow(side, 2));
		}

		double get_height()const
		{
			return sqrt(4 * pow(side, 2) - pow(get_base(), 2)) / 2;
		}

		double get_area()const
		{
			return get_base() * get_height() / 2;
		}

		double get_area_2()const
		{
			return get_base() / 4 * sqrt(4 * pow(side, 2) - pow(get_base(), 2));
		}

		double get_perimeter()const
		{
			return side * 2 + get_base();
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hpen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hpen);
			SelectObject(hdc, hBrush);

			POINT vertex[] =
			{
				{start_x, start_y + side},
				{start_x + get_base(),start_y + side},
				{start_x + get_base() / 2,start_y + side - get_height()}
			};

			::Polygon(hdc, vertex, 3);

			DeleteObject(hpen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны " << side << endl;
			cout << "Площадь 2 вариант " << get_area_2() << endl;
			Triangle::info();
		}
	};

	class RightTriangl :public Triangle
	{
		double side1, side2;

	public:

		RightTriangl(double side1, double side2, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side_1(side1);
			set_side_2(side2);
		}

		~RightTriangl() {}

		double get_side_1()const
		{
			return side1;
		}

		double get_side_2()const
		{
			return side2;
		}

		void set_side_1(double side1)
		{
			if (side1 < limits::MIN_SIZE)side1 = limits::MIN_SIZE;
			if (side1 > limits::MAX_SIZE)side1 = limits::MAX_SIZE;
			this->side1 = side1;
		}

		void set_side_2(double side2)
		{
			if (side2 < limits::MIN_SIZE)side2 = limits::MIN_SIZE;
			if (side2 > limits::MAX_SIZE)side2 = limits::MAX_SIZE;
			this->side2 = side2;
		}

		double get_height()const
		{
			return side2;
		}

		double get_hypotenuse()const
		{
			return sqrt(side1 * side1 + side2 * side2);
		}

		double get_area()const
		{
			return side1 * side2 / 2;
		}

		double get_perimeter()const
		{
			return side1 + side2 + get_hypotenuse();
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hpen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hpen);
			SelectObject(hdc, hBrush);

			POINT vertex[] =
			{
				{start_x,start_y},
				{start_x, start_y + get_height()},
				{start_x + side1,start_y + get_height()},
			};

			::Polygon(hdc, vertex, 3);

			DeleteObject(hpen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Катет 1: " << side1 << endl;
			cout << "Катет 2: " << side2 << endl;
			cout << "Высота: " << get_height() << endl;
			cout << "Гипотенуза: " << get_hypotenuse() << endl;
			Triangle::info();
		}
	};

	class Trapezoid :public Shape
	{
	public:
		Trapezoid(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
		~Trapezoid() {}

		virtual double get_middle_line()const = 0;

		void info()const
		{
			cout << "Высота трапеции: " << get_middle_line() << endl;
			Shape::info();
		}
	};

	class IsoscelesTrapezoid :public Trapezoid
	{
		double side;
		double base_a;
		double base_d;

	public:

		IsoscelesTrapezoid(double side, double base_a, double base_d, SHAPE_TAKE_PARAMETERS) :Trapezoid(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
			set_base_a(base_a);
			set_base_d(base_d);
		}

		~IsoscelesTrapezoid() {}

		double get_side()const
		{
			return side;
		}
		
		double get_base_a()const
		{
			return base_a;
		}

		double get_base_d()const
		{
			return base_d;
		}

		void set_side(double side)
		{
			if (side < limits::MIN_SIZE)side = limits::MIN_SIZE;
			if (side > limits::MAX_SIZE)side = limits::MAX_SIZE;
		}

		void set_base_a(double base_a)
		{
			if (base_a < limits::MIN_SIZE)base_a = limits::MIN_SIZE;
			if (base_a > limits::MAX_SIZE)base_a = limits::MAX_SIZE;
		}

		void set_base_d(double base_d)
		{
			if (base_d < limits::MIN_SIZE)base_d = limits::MIN_SIZE;
			if (base_d > limits::MAX_SIZE)base_d = limits::MAX_SIZE;
		}

		double get_middle_line()const
		{
			return (base_a + base_d) / 2;
		}

		double get_height()const
		{
			return sqrt(pow(side, 2) - pow((base_d - base_a) / 2, 2));
		}

		double get_base_dk()const
		{
			return sqrt(pow(side, 2) - pow(get_height(), 2));
		}

		double get_area()const
		{
			return get_middle_line() * get_height();
		}

		double get_perimeter()const
		{
			return base_a + base_d + 2 * side;
		}

		double get_perimeter_2()const
		{
			return 2 * get_middle_line() + base_a + base_d;
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hpen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hpen);
			SelectObject(hdc, hBrush);

			POINT vertex[] =
			{
				{start_x,start_y + side},
				{start_x+base_d,start_y+base_d},
				{start_x-get_base_dk(),start_y+get_height()},
				{start_x+base_a,start_y}
			};

			::Polygon(hdc, vertex, 4);

			DeleteObject(hpen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Периметр 2 вариант: " << get_perimeter_2() << endl;
			cout << "Средняя линия: " << get_middle_line() << endl;
			cout << "Высота трапеции: " << get_height() << endl;
			Shape::info();
		}

	};
}


void main()
{
	setlocale(LC_ALL, "");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	Geometry::Square square(200, 400, 50, 5, Geometry::Color::blue);
	/*
	cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрат: " << square.get_perimeter() << endl;
	square.draw();
	*/
	square.info();

	Geometry::Rectangle rect(250, 77, 200, 100, 5, Geometry::Color::red);
	rect.info();

	Geometry::Circle rad(100, 100, 300, 5, Geometry::Color::green);
	rad.info();

	Geometry::EquilateralTriangle eq_triangl(300, 700, 50, 5, Geometry::Color::yellow);
	eq_triangl.info();

	Geometry::IsoscelesTriangle is_triangl(200, 600, 80, 5, Geometry::Color::red);
	is_triangl.info();

	Geometry::RightTriangl ri_triangl(150, 50, 850, 50, 5, Geometry::Color::white);
	ri_triangl.info();

	Geometry::IsoscelesTrapezoid is_trapezoid(300, 500, 700, 300, 400, 5, Geometry::Color::green);
	is_trapezoid.info();

}