#ifndef STUDENT_H
#define STUDENT_H
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
#endif // STUDENT_H
