#include "StudentListManager.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QFileDialog>

StudentListManager::StudentListManager(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.clearButton->setStyleSheet("background-color: red; color: white;");

    //for (int i = 1; i < 20; i++) {
    //    addStudent(QString::number(i) + "FirstName", "LastName", true, true, "Informatyka");
    //}

    connect(ui.clearButton, &QPushButton::clicked, this, &StudentListManager::clearButton_clicked);
    connect(ui.editButton, &QPushButton::clicked, this, &StudentListManager::editButton_clicked);
}

StudentListManager::~StudentListManager()
{}

void StudentListManager::addButton_clicked()
{
    ui.clearButton->setStyleSheet("background-color: red; color: white;");
    bool ok;
    QString firstName = QInputDialog::getText(this, tr("Input First Name"),
        tr("First Name:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || firstName.isEmpty()) {
        QMessageBox::warning(this, "error", "First name can't be empty");
        return;
    }

    QString lastName = QInputDialog::getText(this, tr("Input Last Name"),
        tr("Last Name:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || lastName.isEmpty()) {
        QMessageBox::warning(this, "error", "Last name can't be empty");
        return;
    }

    int ret = QMessageBox::question(this, tr("Active Status"),
        tr("Is the student active? (default: no)"),
        QMessageBox::Yes | QMessageBox::No);
    bool isActive = (ret == QMessageBox::Yes);

    ret = QMessageBox::question(this, tr("Study Mode"),
        tr("Is the student full-time? (default: no)"),
        QMessageBox::Yes | QMessageBox::No);
    bool isFullTime = (ret == QMessageBox::Yes);

    QString major = QInputDialog::getText(this, tr("Input Major"),
        tr("Major:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || major.isEmpty()) {
        QMessageBox::warning(this, "error", "Major can't be empty");
        return;
    }

    addStudent(firstName, lastName, isActive, isFullTime, major);
    QMessageBox::information(this, tr("Success"), tr("Student added successfully."));
}

void StudentListManager::editButton_clicked()
{
    int currentRow = ui.listWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, tr("No selection"), tr("Please select a student to edit."));
        return;
    }

    Student selected = getStudentFromCurrent();

    bool ok;
    QString firstName = QInputDialog::getText(this, tr("Edit First Name"),
        tr("First Name: (pass: empty)"), QLineEdit::Normal,
        "", &ok);
    if (!ok) {
        QMessageBox::warning(this, "error", "input error");
        return;
    }
    else if (firstName.isEmpty()) {
        firstName = selected.getFirstName();
    }

    QString lastName = QInputDialog::getText(this, tr("Edit Last Name"),
        tr("Last Name: (pass: empty)"), QLineEdit::Normal,
        "", &ok);
    if (!ok) {
        QMessageBox::warning(this, "error", "input error");
        return;
    }
    else if (lastName.isEmpty()) {
        lastName = selected.getLastName();
    }

    int ret = QMessageBox::question(this, tr("Active Status"),
        tr("Is the student active? (default: no)"),
        QMessageBox::Yes | QMessageBox::No);
    bool isActive = (ret == QMessageBox::Yes);

    ret = QMessageBox::question(this, tr("Study Mode"),
        tr("Is the student full-time? (default: no)"),
        QMessageBox::Yes | QMessageBox::No);
    bool isFullTime = (ret == QMessageBox::Yes);

    QString major = QInputDialog::getText(this, tr("Edit Major"),
        tr("Major: (pass: empty)"), QLineEdit::Normal,
        "", &ok);
    if (!ok) {
        QMessageBox::warning(this, "error", "input error");
        return;
    }
    else if (major.isEmpty()) {
        major = selected.getMajor();
    }

    editStudent(currentRow, firstName, lastName, isActive, isFullTime, major);
    QMessageBox::information(this, tr("Success"), tr("Student edited successfully."));
}

void StudentListManager::delButton_clicked()
{
    int currentRow = ui.listWidget->currentRow();
    if (currentRow >= 0) {
        ui.listWidget->setRowHidden(currentRow, true);
        QMessageBox::information(this, tr("Success"), tr("Student deleted successfully."));
    }
    else {
        QMessageBox::warning(this, tr("No selection"), tr("Please select a student to delete."));
    }
}

void StudentListManager::clearButton_clicked()
{
    ui.listWidget->clear();
    ui.clearButton->setStyleSheet("background-color: green; color: white;");
    QMessageBox::information(this, tr("Success"), tr("All students cleared successfully."));
}

void StudentListManager::addStudent(const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major)
{
    Student student(firstName, lastName, isActive, isFullTime, major);
    ui.listWidget->addItem(student.getFullName() + " (" + major + ", " + (isActive ? "Active" : "Inactive") + ", " + (isFullTime ? "Full-Time" : "Part-Time") + ")");
}

void StudentListManager::editStudent(int index, const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major)
{
    Student student(firstName, lastName, isActive, isFullTime, major);
    QListWidgetItem* item = ui.listWidget->item(index);
    if (item) {
        item->setText(student.getFullName() + " (" + major + ", " + (isActive ? "Active" : "Inactive") + ", " + (isFullTime ? "Full-Time" : "Part-Time") + ")");
    }
}


void StudentListManager::saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Student List"), "", tr("Text Files (*.txt);;All Files (*)"));
    QFile file(fileName);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "error", "No file chosen/File error");
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < ui.listWidget->count(); ++i) {
        QListWidgetItem* item = ui.listWidget->item(i);
        if (item) {
            if (!item->isHidden()) {
                out << item->text() << "\n";
            }
        }
    }

    QMessageBox::information(this, "info", "student list saved successfully");

    file.close();
}

void StudentListManager::loadButton_clicked()
{
    QVector<int> errorLines;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Student List"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "error", "No file chosen/File error");
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "error", "No file chosen/File error");
        return;
    }



    QTextStream in(&file);
    
    int i = 1;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList inputs;
        QString firstName, lastName, major;
        bool isActive, isFullTime;
        inputs = line.split(u' ');
        firstName = inputs[0];
        lastName = inputs[1];

        if (inputs[2][0] != '(') {
            
            errorLines.append(i);
            i++;
            continue;
        }

        major = inputs[2].sliced(1);
        major.chop(1);
        
        if (inputs[3].size() == 7) {
            isActive = true;
        }
        else {
            isActive = false;
        }

        if (inputs[4].size() == 10) {
            isFullTime = true;
        }
        else {
            isFullTime = false;
        }

        addStudent(firstName, lastName, isActive, isFullTime, major);
        i++;
    }

    if (errorLines.isEmpty()) {
        QMessageBox::information(this, "info", "student list loaded successfully");
    }
    else {
        QString errorLinesString;
        for (int i = 0; i < errorLines.size(); i++) {
            errorLinesString.append(QString::number(errorLines[i]));
            errorLinesString.append((QChar)' ');
        }
        QMessageBox::warning(this, "error", "text formating error in lines: " + errorLinesString);
    }

    file.close();
}

Student StudentListManager::getStudentFromCurrent()
{
    QList<QListWidgetItem*> selectedItems = ui.listWidget->selectedItems();
    QListWidgetItem* selectedItem = selectedItems.first();
    QString line = selectedItem->text();
    QStringList inputs;
    QString firstName, lastName, major;
    bool isActive, isFullTime;
    inputs = line.split(u' ');
    firstName = inputs[0];
    lastName = inputs[1];
    major = inputs[2].sliced(1);
    major.chop(1);

    if (inputs[3].size() == 7) {
        isActive = true;
    }
    else {
        isActive = false;
    }

    if (inputs[4].size() == 10) {
        isFullTime = true;
    }
    else {
        isFullTime = false;
    }

    Student current(firstName, lastName, isActive, isFullTime, major);
    return current;
}