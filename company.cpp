#include "company.h"

Company::Company(QString name, QString post, int salary, int vacation, bool higher_education, int min, int max, int experience)
    : name(name)
    , post(post)
    , salary(salary)
    , vacation(vacation)
    , age({min, max})
    , experience(experience)
    , higher_education(higher_education)
{
}
Company::Company(QJsonObject data)
{
    name = data["name"].toString();
    post = data["post"].toString();
    salary = data["salary"].toInt();
    vacation = data["vacation"].toInt();
    higher_education = data["education"].toBool();
    experience = data["experience"].toInt();
    age[0] = data["minAge"].toInt();
    age[1] = data["maxAge"].toInt();
}
void Company::setPost(QString post)
{
    this->post = post;
}
void Company::setSalary(int salary)
{
    this->salary = salary;
}
void Company::setVacation(int vacation)
{
    this->vacation = vacation;
}
void Company::setEducation(bool isHigher)
{
    higher_education = isHigher;
}
void Company::setMinMaxAge(int min, int max)
{
    age[0] = min;
    age[1] = max;
}
void Company::setExperience(int experience)
{
    this->experience = experience;
}

QString Company::getName()
{
    return name;
}
QString Company::getPost()
{
    return post;
}
int Company::getSalary()
{
    return salary;
}
int Company::getVacation()
{
    return vacation;
}
int Company::getExperience()
{
    return experience;
}
int* Company::getAge()
{
    return age;
}
bool Company::getEducation()
{
    return higher_education;
}

QJsonObject Company::getSerializedData()
{
    return QJsonObject {
        {"name", name},
        {"post", post},
        {"salary", salary},
        {"vacation", vacation},
        {"education", higher_education},
        {"experience", experience},
        {"minAge", age[0]},
        {"maxAge", age[1]}
    };
}
