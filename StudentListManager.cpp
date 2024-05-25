#include "StudentListManager.h"

StudentListManager::StudentListManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    for (int i = 1; i < 20; i++)
    {
        ui.listWidget->addItem("Student nr " + QString::number(i));
    }
}

StudentListManager::~StudentListManager()
{}

void StudentListManager::addButton_clicked()
{
    int size = ui.listWidget->count() + 1;
    ui.listWidget->addItem("Student nr " + QString::number(size));

}

void StudentListManager::delButton_clicked()
{
    ui.listWidget->setRowHidden(ui.listWidget->currentRow(), true);
}