﻿#include<iostream>
#include<string>
using namespace std;

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	int age;

public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}

	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//---------------------Constructors----------------------

	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}

};

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}

	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//---------------------Constructors----------------------

	Student(HUMAN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//------------------------Methods------------------------

	void info()const
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}

};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experiebce
#define TEACHER_GIVE_PARAMETERS speciality, experiebce

class Teacher :public Human
{
	std::string speciality;
	int experiebce;

public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int set_experiedce()const
	{
		return experiebce;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experiedce(int experiebce)
	{
		this->experiebce = experiebce;
	}

	//---------------------Constructors----------------------

	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experiedce(experiebce);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//------------------------Methods------------------------

	void info()const
	{
		Human::info();
		cout << speciality << " " << experiebce << " лет." << endl;
	}
};

#define GRADUATE_TAKE_PARAMETERS  const std::string& subject
#define GRADUATE_GIVE_PARAMETERS  subject

class Graduate :public Student
{
	std::string subject;

public:

	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}

	//---------------------Constructors----------------------

	Graduate(HUMAN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS,GRADUATE_TAKE_PARAMETERS)
		:Student(HUMAN_GIVE_PARAMETERS,STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}

	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//------------------------Methods------------------------

	void info()const
	{
		Student::info();
		cout << subject << " " << endl;
	}
};

//#define INHERITANCE_CHECK
#define POLIMORPHISM

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE_CHECK

	Human human("Тупенко", "Василий", 20);
	human.info();

	Student student("Иванов", "Иван", 18, "IT", "PV_211", 12, 100);
	student.info();

	Teacher teacher("Einstein", "Albert", 143, "Astronomy", 110);
	teacher.info();

	Graduate graduate("Петров", "Николай", 21, "IT", "PV_211", 10, 80, "Организация защиты безопасности сети");
	graduate.info();

#endif // INHERITANCE_CHECK

//---------------------Ganeralisation(ApCast)-----------------

	Human* group[] =
	{
		new Student("Pinkman", "Jassie", 20, "Chemistry", "WW_220", 89, 92),
		new Student("Vercetti", "Tomas", 30, "Criminalistic", "Vice", 98, 99),
		new Teacher("Whaite", "Walter", 50, "Chermistry", 25),
		new Teacher("Diaz", "Ricardo", 50, "Wepons distribution", 20),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "OBN", 95, 75, "How to catch Helizenberg")
	};

	cout << sizeof(group) / sizeof(group[0]) << endl;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->info();
		cout << "\n--------------------------------\n";
	}
}
