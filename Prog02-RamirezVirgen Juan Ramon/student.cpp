#include "student.h"
using namespace std;
Student::Student(): code(0),name(""),degree("") {}

Student::Student(Student& s)
{
    code = s.code;
    name = s.name;
    degree = s.degree;
}

Student::Student(int c, string n , string d)
{
    code = c;
    name = n;
    degree = d;
}

void Student::setCode(int c)
{
    code = c;
}

void Student::setName(string n)
{
    name = n;
}

void Student::setDegree(string d)
{
    degree = d;
}

int Student::getCode()
{
    return code;
}

string Student::getName()
{
    return name;
}

string Student::getDegree()
{
    return degree;
}

