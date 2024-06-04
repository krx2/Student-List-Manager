#include "StudentListManager.h"
#include <QInputDialog>
#include <QMessageBox>

StudentListManager::StudentListManager(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.clearButton->setStyleSheet("background-color: red; color: white;");

    // Add initial students
    for (int i = 1; i < 20; i++) {
        addStudent(QString::number(i) + "FirstName", "LastName", true, true, "Informatyka");
    }

    connect(ui.clearButton, &QPushButton::clicked, this, &StudentListManager::clearButton_clicked);
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
        return;
    }

    QString lastName = QInputDialog::getText(this, tr("Input Last Name"),
        tr("Last Name:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || lastName.isEmpty()) {
        return;
    }

    int ret = QMessageBox::question(this, tr("Active Status"),
        tr("Is the student active?"),
        QMessageBox::Yes | QMessageBox::No);
    bool isActive = (ret == QMessageBox::Yes);

    ret = QMessageBox::question(this, tr("Study Mode"),
        tr("Is the student full-time?"),
        QMessageBox::Yes | QMessageBox::No);
    bool isFullTime = (ret == QMessageBox::Yes);

    QString major = QInputDialog::getText(this, tr("Input Major"),
        tr("Major:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || major.isEmpty()) {
        return;
    }

    addStudent(firstName, lastName, isActive, isFullTime, major);
}

void StudentListManager::delButton_clicked()
{
    ui.listWidget->setRowHidden(ui.listWidget->currentRow(), true);
}

void StudentListManager::clearButton_clicked()
{
    ui.listWidget->clear();
    ui.clearButton->setStyleSheet("background-color: green; color: white;");
}

// Function to add a student to the list
void StudentListManager::addStudent(const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major)
{
    Student student(firstName, lastName, isActive, isFullTime, major);
    ui.listWidget->addItem(student.getFullName() + " (" + major + ", " + (isActive ? "Active" : "Inactive") + ", " + (isFullTime ? "Full-Time" : "Part-Time") + ")");
}
