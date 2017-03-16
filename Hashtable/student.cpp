/***************************************************************************
 * Student Class
 *
 * Author: Chaoyang Liu
 * E-main: chaoyanglius@outlook.com
 *
 * Software License Agreement (GPL License)
 * Copyright (c) 2017, Chaoyang Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
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

