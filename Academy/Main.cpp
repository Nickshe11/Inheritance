#include<iostream>
#include <string>
using namespace std;

#define delimiter "\n__________________\n"
#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age
class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}

	//Constructors
	Human(const std::string& last_name, const std::string& first_name, unsigned int age) :
		last_name(last_name), first_name(first_name), age(age)
	{
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//Methods
	void print()const
	{
		cout << last_name << " " << first_name << " " << age << " лет.\n";
	}
};

#define STUDENT_TAKE_PARAMETERS const std::string& specialty, const std::string& group, double rating, double attendance
#define student_take_parameters specialty, group, rating, attendance

class Student :public Human
{
	std::string specialty;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_specialty()const
	{
		return specialty;
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
	void set_specialty(const std::string& specialty)
	{
		this->specialty = specialty;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void get_attendance(double attendance)
	{
		this->attendance = attendance;
	}
	//Constructors
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		this->specialty = specialty;
		this->group = group;
		this->rating = rating;
		this->attendance = attendance;
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	//Methods
	void print()const
	{
		Human::print();
		cout << specialty << " " << group << " " << rating << " " << attendance << endl;
	}
};

class Teacher :public Human
{
	std::string specialty;
	unsigned int experience;
public:
	const std::string& get_specialty()const
	{
		return specialty;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_specialty(const std::string& specialty)
	{
		this->specialty = specialty;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}
	//Constructors
	Teacher(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& specialty, unsigned int experience
	) :Human(last_name, first_name, age)
	{
		set_specialty(specialty);
		set_experience(experience);
		cout << "TConstrurtor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//Methods
	void print()const
	{
		Human::print();
		cout << specialty << " " << experience << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Human human("Vercetti", "Tommy", 25);
	human.print();
	cout << delimiter << endl;
	Student stud("Pinkman", "Jessie", 25, "Chemistry", "WW220", 90, 95);
	stud.print();
	cout << delimiter << endl;
	Teacher professor("White", "Walter", 50, "Chemistry", 20);
	professor.print();
}