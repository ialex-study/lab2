#include "employee.h"

Employee::Employee(QString fullName, QString birthDate, QString post, bool education, int salary, QList<QList<QString>> previousPosts)
    : fullName(fullName)
    , birthDate(birthDate)
    , post(post)
    , higherEducation(education)
    , salary(salary)
{
    for(int i = 0; i < previousPosts.size(); i++)
    {
        this->previousPosts.append(previousPosts[i][0]);
        previousExps.append(previousPosts[i][1].toInt());
    }
}
Employee::Employee(QJsonObject data)
{
    fullName = data["fullName"].toString();
    birthDate = data["birthDate"].toString();
    post = data["post"].toString();
    higherEducation = data["education"].toBool();
    salary = data["salary"].toInt();
    QJsonArray temp = data["previousPosts"].toArray();
    for(int i = 0; i < temp.size(); i++)
    {
        previousPosts.append(temp[i].toString());
    }
    temp = data["previousExps"].toArray();
    for(int i = 0; i < temp.size(); i++)
    {
        previousExps.append(temp[i].toInt());
    }
}
int Employee::getAge()
{
    return 2021 - birthDate.midRef(6, 4).toInt();
}
QJsonObject Employee::getSerializedData()
{
    QJsonArray postsData, expsData;
    for(int i = 0; i < previousPosts.size(); i++)
    {
        postsData.append(previousPosts[i]);
        expsData.append(previousExps[i]);
    }
    return QJsonObject {
        {"fullName", fullName},
        {"birthDate", birthDate},
        {"post", post},
        {"education", higherEducation},
        {"salary", salary},
        {"previousPosts", postsData},
        {"previousExps", expsData}
    };
}

void Employee::setName(QString fullName)
{
    this->fullName = fullName;
}
void Employee::setBirth(QString birthDate)
{
    this->birthDate = birthDate;
}
void Employee::setPost(QString post)
{
    this->post = post;
}
void Employee::setSalary(int salary)
{
    this->salary = salary;
}
void Employee::setEducation(bool isHigher)
{
    this->higherEducation = isHigher;
}
void Employee::addPreviousPost(QString post, int experience)
{
    previousPosts.append(post);
    previousExps.append(experience);
}
void Employee::deletePreviousPost(QString post)
{
    int index = previousPosts.indexOf(post);
    previousPosts.removeAt(index);
    previousExps.removeAt(index);
}

QString Employee::getName()
{
    return fullName;
}
QString Employee::getBirthDate()
{
    return birthDate;
}
QString Employee::getPost()
{
    return post;
}
bool Employee::getEducation()
{
    return higherEducation;
}
int Employee::getSalary()
{
    return salary;
}
QList<QList<QString>> Employee::getPreviousPosts()
{
    QList<QList<QString>> result;
    for(int i = 0; i < previousPosts.size(); i++)
    {
        result.append(QList<QString> {
            previousPosts[i], QString::number(previousExps[i])
        });
    }
    return result;
}
