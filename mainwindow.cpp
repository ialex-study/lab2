#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , employeesArr(5)
    , companiesArr(5)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();

    ui->companiesTable_6->setColumnCount(7);
    ui->tableWidget_2->setColumnCount(6);
    updateFields();
}

MainWindow::~MainWindow()
{
    delete fileMenu;
    delete newAct;
    delete openAct;
    delete saveAct;
    delete ui;
}
void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
}
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
}
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
void MainWindow::newFile()
{
    employeesArr.deleteAll();
    companiesArr.deleteAll();
    updateFields();
}
void MainWindow::open()
{
    companiesArr.deleteAll();
    employeesArr.deleteAll();

    // Выбираем файл
    QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("Open Json File"),
                                                       QString(),
                                                       tr("JSON (*.json)"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    // Считываем весь файл
    QByteArray savedData = file.readAll();

    QJsonObject *readObject = new QJsonObject(QJsonDocument(QJsonDocument::fromJson(savedData)).object());
    QJsonArray employeesArray = readObject->take("employeesArray").toArray();
    QJsonArray companiesArray = readObject->take("companiesArray").toArray();

    for(int i = 0; i < companiesArray.size(); i++)
    {
       Company* temp = new Company(companiesArray[i].toObject());
       companiesArr.addObj(temp);
    }
    for(int i = 0; i < employeesArray.size(); i++)
    {
       Employee* temp = new Employee(employeesArray[i].toObject());
       employeesArr.addObj(temp);
    }
    delete readObject;
    file.close();
    updateFields();
}
void MainWindow::save()
{
    // Выбираем файл
    QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Open Json File"),
                                                        QString(),
                                                        tr("JSON (*.json)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QJsonArray *employeesArray = new QJsonArray();
    QJsonArray *companiesArray = new QJsonArray();
    for(int i = 0; i < employeesArr.getCurrentSize(); i++)
    {
        employeesArray->append(QJsonValue(employeesArr[i]->getSerializedData()));
    }
    for(int i = 0; i < companiesArr.getCurrentSize(); i++)
    {
        companiesArray->append(QJsonValue(companiesArr[i]->getSerializedData()));
    }
    QJsonObject *data = new QJsonObject({
                                            {"employeesArray", *employeesArray},
                                            {"companiesArray", *companiesArray}
                                        });
    file.write(QJsonDocument(*data).toJson());
    file.close();
    delete data;
    delete employeesArray;
    delete companiesArray;
}
void MainWindow::updateFields()
{
    for(int i = 0; i < employeesArr.getCurrentSize(); i++)
    {
        int index = i;
        for(int j = i + 1; j < employeesArr.getCurrentSize(); j++)
        {
            if(employeesArr[index]->getName() > employeesArr[j]->getName())
            {
                index = j;
            }
        }
        Employee* min = new Employee(employeesArr[index]->getSerializedData());
        employeesArr.setObject(employeesArr[i], index);
        employeesArr.setObject(min, i);
    }
    for(int i = 0; i < companiesArr.getCurrentSize(); i++)
    {
        int index = i;
        for(int j = i + 1; j < companiesArr.getCurrentSize(); j++)
        {
            if(companiesArr[index]->getName() > companiesArr[j]->getName())
            {
                index = j;
            }
        }
        Company* min = new Company(companiesArr[index]->getSerializedData());
        companiesArr.setObject(companiesArr[i], index);
        companiesArr.setObject(min, i);
    }

    QTableWidgetItem *tempItem;
    QString tempString;

    ui->companiesTable_6->setRowCount(companiesArr.getCurrentSize() + 1);
    tempItem = new QTableWidgetItem("Name");
    ui->companiesTable_6->setItem(0, 0, tempItem);
    tempItem = new QTableWidgetItem("Post");
    ui->companiesTable_6->setItem(0, 1, tempItem);
    tempItem = new QTableWidgetItem("Salary");
    ui->companiesTable_6->setItem(0, 2, tempItem);
    tempItem = new QTableWidgetItem("Vacation");
    ui->companiesTable_6->setItem(0, 3, tempItem);
    tempItem = new QTableWidgetItem("Experience");
    ui->companiesTable_6->setItem(0, 4, tempItem);
    tempItem = new QTableWidgetItem("Age");
    ui->companiesTable_6->setItem(0, 5, tempItem);
    tempItem = new QTableWidgetItem("Education");
    ui->companiesTable_6->setItem(0, 6, tempItem);
    for(int i = 0; i < companiesArr.getCurrentSize(); i++)
    {
        tempItem = new QTableWidgetItem(companiesArr[i]->getName());
        ui->companiesTable_6->setItem(i + 1, 0, tempItem);
        tempItem = new QTableWidgetItem(companiesArr[i]->getPost());
        ui->companiesTable_6->setItem(i + 1, 1, tempItem);
        tempItem = new QTableWidgetItem(tempString.setNum(companiesArr[i]->getSalary()));
        ui->companiesTable_6->setItem(i + 1, 2, tempItem);
        tempItem = new QTableWidgetItem(tempString.setNum(companiesArr[i]->getVacation()));
        ui->companiesTable_6->setItem(i + 1, 3, tempItem);
        tempItem = new QTableWidgetItem(tempString.setNum(companiesArr[i]->getExperience()));
        ui->companiesTable_6->setItem(i + 1, 4, tempItem);
        QString age(tempString.setNum(companiesArr[i]->getAge()[0]));
        age += " - " + tempString.setNum(companiesArr[i]->getAge()[1]);
        tempItem = new QTableWidgetItem(age);
        ui->companiesTable_6->setItem(i + 1, 5, tempItem);
        tempString = companiesArr[i]->getEducation() ? "Higher Education" : "No higher Education";
        tempItem = new QTableWidgetItem(tempString);
        ui->companiesTable_6->setItem(i + 1, 6, tempItem);
    }

    ui->tableWidget_2->setRowCount(employeesArr.getCurrentSize() + 1);
    tempItem = new QTableWidgetItem("Full name");
    ui->tableWidget_2->setItem(0, 0, tempItem);
    tempItem = new QTableWidgetItem("Birth date");
    ui->tableWidget_2->setItem(0, 1, tempItem);
    tempItem = new QTableWidgetItem("Post");
    ui->tableWidget_2->setItem(0, 2, tempItem);
    tempItem = new QTableWidgetItem("Salary");
    ui->tableWidget_2->setItem(0, 3, tempItem);
    tempItem = new QTableWidgetItem("Education");
    ui->tableWidget_2->setItem(0, 4, tempItem);
    tempItem = new QTableWidgetItem("Previous posts: experience");
    ui->tableWidget_2->setItem(0, 5, tempItem);
    for(int i = 0; i < employeesArr.getCurrentSize(); i++)
    {
        tempItem = new QTableWidgetItem(employeesArr[i]->getName());
        ui->tableWidget_2->setItem(i + 1, 0, tempItem);
        tempItem = new QTableWidgetItem(employeesArr[i]->getBirthDate());
        ui->tableWidget_2->setItem(i + 1, 1, tempItem);
        tempItem = new QTableWidgetItem(employeesArr[i]->getPost());
        ui->tableWidget_2->setItem(i + 1, 2, tempItem);
        tempItem = new QTableWidgetItem(tempString.setNum(employeesArr[i]->getSalary()));
        ui->tableWidget_2->setItem(i + 1, 3, tempItem);
        tempString = employeesArr[i]->getEducation() ? "Higher Education" : "No higher Education";
        tempItem = new QTableWidgetItem(tempString);
        ui->tableWidget_2->setItem(i + 1, 4, tempItem);
        tempString = "";
        QList<QList<QString>> previousPosts = employeesArr[i]->getPreviousPosts();
        for(int i = 0; i < previousPosts.size(); i++)
        {
            tempString += previousPosts[i][0] + ": " + previousPosts[i][1] + "\n";
        }
        tempItem = new QTableWidgetItem(tempString);
        ui->tableWidget_2->setItem(i + 1, 5, tempItem);
    }

    QString eligibleEmpls = "";
    QList<QString> withJob;
    QString withoutJob = "";
    for(int i = 0; i < companiesArr.getCurrentSize(); i++)
    {
        eligibleEmpls += companiesArr[i]->getName() + ": ";
        for(int j = 0; j < employeesArr.getCurrentSize(); j++)
        {
            if(
                companiesArr[i]->getPost() == employeesArr[j]->getPost() &&
                companiesArr[i]->getAge()[0] <= employeesArr[j]->getAge() &&
                companiesArr[i]->getAge()[1] >= employeesArr[j]->getAge() &&
                companiesArr[i]->getEducation() == employeesArr[j]->getEducation()
            )
            {
                if(companiesArr[i]->getExperience() == 0) {
                    eligibleEmpls += employeesArr[j]->getName() + ", ";
                    withJob.append(employeesArr[j]->getName());
                }
                else {
                    QList<QList<QString>> prevPosts = employeesArr[j]->getPreviousPosts();
                    for(int k = 0; k < prevPosts.size(); k++)
                    {
                        if(companiesArr[i]->getPost() == prevPosts[k][0] && companiesArr[i]->getExperience() <= prevPosts[k][1].toInt()) {
                            eligibleEmpls += employeesArr[j]->getName() + ", ";
                            withJob.append(employeesArr[j]->getName());
                        }
                    }
                }
            }
        }
        eligibleEmpls += "\n";
        eligibleEmpls.replace(", \n", "\n");
        eligibleEmpls.replace(": \n", ": -\n");
    }
    for(int i = 0; i < employeesArr.getCurrentSize(); i++)
    {
        if(withJob.indexOf(employeesArr[i]->getName()) == -1) {
            withoutJob += employeesArr[i]->getName() + "\n";
        }
    }
    ui->eligibleEmployeesList->setText(eligibleEmpls);
    ui->textBrowser_16->setText(withoutJob);
}

void MainWindow::on_addCompany_6_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Name, post, salary, vacation, education(y, n), age, exp:")
                                         , QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        int salary, vacation, min, max, experience;
        bool higher_education;
        QString name, post;

        name = list[0];
        post = list[1];
        salary = list[2].toInt();
        vacation = list[3].toInt();
        higher_education = list[4] == "y" ? true : false;
        min = list[5].toInt();
        max = list[6].toInt();
        experience = list[7].toInt();

        Company *company = new Company(name, post, salary, vacation, higher_education, min, max, experience);
        companiesArr.addObj(company);
    }
    updateFields();
}

void MainWindow::on_addEmployee_6_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Fullname, birth date, post, education(y, n), salary, previout posts: exp")
                                         , QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");


        QList<QList<QString>> previousPosts;
        int salary;
        bool higher_education;
        QString fullName, birthDate, post;


        fullName = list[0] + " " + list[1];
        birthDate = list[2];
        post = list[3];
        higher_education = list[4] == "y" ? true : false;
        salary = list[5].toInt();
        for(int i = 6; i < list.size(); i += 2)
        {
            previousPosts.append(QList<QString>({
                                                    list[i], list[i + 1]
                                                }));
        }


        Employee *employee = new Employee(fullName, birthDate, post, higher_education, salary, previousPosts);
        employeesArr.addObj(employee);
    }
    updateFields();
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Company number:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {
        delete companiesArr.removeObj(text.toInt() - 2);
    }
    updateFields();
}

void MainWindow::on_pushButton_2_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Employee number:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {
        delete employeesArr.removeObj(text.toInt() - 2);
    }
    updateFields();
}
