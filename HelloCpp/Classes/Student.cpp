#include "Student.h"
#include "cocos2d.h"

Student::Student(void)
{
}


Student::~Student(void)
{
    cocos2d::CCLog("delete data");
}
Student::Student(std::string name,int age,std::string sex)
{
    this->name=name;
    this->age=age;
    this->sex=sex;
}