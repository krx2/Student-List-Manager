#ifndef STUDENT_H
#define STUDENT_H

#include "Human.h"

class Student : public Human {
public:
    Student(const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major);

    bool getIsActive() const;
    bool getIsFullTime() const;
    QString getMajor() const;

private:
    bool isActive;
    bool isFullTime;
    QString major;
};

#endif // STUDENT_H
