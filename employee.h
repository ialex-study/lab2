#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

class Employee
{
    QString fullName, birthDate, post;
    bool higherEducation;
    int salary;
    QList<QString> previousPosts;
    QList<int> previousExps;
public:
    Employee(QString fullName, QString birthDate, QString post, bool education, int salary, QList<QList<QString>> previousPosts);
    Employee(QJsonObject data);

    void setName(QString fullName);
    void setBirth(QString birthDate);
    void setPost(QString post);
    void setSalary(int salary);
    void setEducation(bool isHigher);
    void addPreviousPost(QString post, int experience);
    void deletePreviousPost(QString post);

    QString getName();
    QString getBirthDate();
    int getAge();
    QString getPost();
    bool getEducation();
    int getSalary();
    QList<QList<QString>> getPreviousPosts();

    QJsonObject getSerializedData();
};

#endif // EMPLOYEE_H
