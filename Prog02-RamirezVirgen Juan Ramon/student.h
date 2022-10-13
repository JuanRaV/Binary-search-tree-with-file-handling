#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include <string>
#include <ostream>
using namespace std;
class Student{
    private:
        int code;
        string name;
        string degree;
    public:
        Student();
        Student(Student&);
        Student(int,string,string);


        void setCode(int);
        void setName(string);
        void setDegree(string);

        int getCode();
        string getName();
        string getDegree();


        void operator=( Student s)
        {
            code = s.code;
            name = s.name;
            degree = s.degree;
        }

        bool operator < ( Student s)
        {
            return code < s.code;
        }

        bool operator == ( Student s)
        {
            return code == s.code;
        }

        bool operator <= (Student s)
        {
            return *this < s or *this == s;
        }

        bool operator > (Student s)
        {
            return ! (*this <= s);
        }

        bool operator >= (Student s)
        {
            return ! (*this < s);
        }

        friend ostream& operator<<(ostream& os, const Student& st){
            os<<st.code<<",";

            return os;
        };

};

#endif // STUDENT_H_INCLUDED
