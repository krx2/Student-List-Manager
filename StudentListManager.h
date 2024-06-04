#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StudentListManager.h"
#include "Student.h"

class StudentListManager : public QMainWindow
{
    Q_OBJECT

public:
    StudentListManager(QWidget* parent = nullptr);
    ~StudentListManager();

private:
    Ui::StudentListManagerClass ui;
    void addStudent(const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major);
    void editStudent(int index, const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major);

private slots:
    void addButton_clicked();
    void delButton_clicked();
    void clearButton_clicked();
    void editButton_clicked();
    void loadButton_clicked();
    void saveButton_clicked();
};
