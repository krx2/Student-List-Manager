#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student {
public:
    Student(const QString& firstName, const QString& lastName);

    QString getFirstName() const;
    QString getLastName() const;
    QString getFullName() const;

private:
    QString firstName;
    QString lastName;
};

#endif // STUDENT_H

