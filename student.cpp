#include "student.h"

Student::Student(string sname, string sage, string sphoneNumber, string ssex,
                 string s_class, Student *per)
{
    name=sname;
    age=sage;
    phoneNumber=sphoneNumber;
    sex=ssex;
    _class=s_class;
    link=per;
}
Student::Student(Student *per)
{
    link=per;
}
