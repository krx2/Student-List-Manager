#include "StudentListManager.h"
#include "Student.h"
#include <QInputDialog>

StudentListManager::StudentListManager(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.clearButton->setStyleSheet("background-color: red; color: white;");

    // Add initial students
    for (int i = 1; i < 20; i++) {
        addStudent(QString::number(i) + "FirstName", "LastName");
    }

    //Wieszczemu nie da siê tego podpi¹æ w designerze? Czemu nie pokazuje slota clearButton do wybrania?
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
        // User cancelled the dialog or input is empty
        return;
    }

    QString lastName = QInputDialog::getText(this, tr("Input Last Name"),
        tr("Last Name:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || lastName.isEmpty()) {
        // User cancelled the dialog or input is empty
        return;
    }

    addStudent(firstName, lastName);
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
void StudentListManager::addStudent(const QString& firstName, const QString& lastName)
{
    Student student(firstName, lastName);
    ui.listWidget->addItem(student.getFullName());
}