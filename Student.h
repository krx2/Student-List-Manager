#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student {
public:
    Student(const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major);

    QString getFirstName() const;
    QString getLastName() const;
    QString getFullName() const;
    bool getIsActive() const;
    bool getIsFullTime() const;
    QString getMajor() const;

private:
    QString firstName;
    QString lastName;
    bool isActive;
    bool isFullTime;
    QString major;
};

#endif // STUDENT_H
