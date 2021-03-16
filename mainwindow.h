#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QLabel>
#include <QContextMenuEvent>
#include "container.h"
#include "container.cpp"
#include "employee.h"
#include "company.h"
#include <QTableWidgetItem>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>
#include <QInputDialog>
#include <QStringList>

template class Container<Employee>;
template class Container<Company>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;

    Container<Employee> employeesArr;
    Container<Company> companiesArr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateFields();
private slots:
    void newFile();
    void open();
    void save();
    void on_addCompany_6_clicked();

    void on_addEmployee_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU
private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
};
#endif // MAINWINDOW_H
