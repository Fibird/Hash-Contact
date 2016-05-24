#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include <iostream>

using namespace std;
struct Student
{
    string name;
    string age;
    string phoneNumber;
    string sex;
    string _class;
    Student *link;

    Student(string sname, string sage, string sphoneNumber, string ssex,
            string s_class, Student *per=NULL);
    Student(Student *per=NULL);
};


#endif // STUDENT_H_INCLUDED
