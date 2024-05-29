#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StudentListManager.h"

class StudentListManager : public QMainWindow
{
    Q_OBJECT

public:
    StudentListManager(QWidget* parent = nullptr);
    ~StudentListManager();

private:
    Ui::StudentListManagerClass ui;
    void addStudent(const QString& firstName, const QString& lastName);

private slots:
    void addButton_clicked();
    void delButton_clicked();
    void clearButton_clicked();

};
