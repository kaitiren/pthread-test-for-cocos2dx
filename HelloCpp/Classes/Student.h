
#pragma once

#include <string>
class Student
{
public:
    Student(void);
    Student(std::string name,int age,std::string sex);
    ~Student(void);
    
    std::string name;
    int age;
    std::string sex;
};