#include "StudentListManager.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
StudentListManager::StudentListManager(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.clearButton->setStyleSheet("background-color: red; color: white;");

    for (int i = 1; i < 20; i++) {
        addStudent(QString::number(i) + "FirstName", "LastName", true, true, "Informatyka");
    }

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
void StudentListManager::editButton_clicked()
{
    int currentRow = ui.listWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, tr("No selection"), tr("Please select a student to edit."));
        return;
    }

    bool ok;
    QString firstName = QInputDialog::getText(this, tr("Edit First Name"),
        tr("First Name:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || firstName.isEmpty()) {
        return;
    }

    QString lastName = QInputDialog::getText(this, tr("Edit Last Name"),
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

    QString major = QInputDialog::getText(this, tr("Edit Major"),
        tr("Major:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || major.isEmpty()) {
        return;
    }

    editStudent(currentRow, firstName, lastName, isActive, isFullTime, major);
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