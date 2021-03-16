#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include <QJsonObject>

class Company
{
    QString name, post;
    int salary, vacation, experience, age[2];
    bool higher_education;
public:
    Company(QString name, QString post, int salary, int vacation, bool higher_education, int min, int max, int experience);
    Company(QJsonObject data);

    void setPost(QString post);
    void setSalary(int salary);
    void setVacation(int vacation);
    void setEducation(bool isHigher);
    void setMinMaxAge(int min, int max);
    void setExperience(int experience);

    QString getName();
    QString getPost();
    int getSalary();
    int getVacation();
    int getExperience();
    int* getAge();
    bool getEducation();

    QJsonObject getSerializedData();
};

#endif // COMPANY_H
