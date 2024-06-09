#include "Student.h"

Student::Student(const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major)
    : Human(firstName, lastName), isActive(isActive), isFullTime(isFullTime), major(major) {}

bool Student::getIsActive() const {
    return isActive;
}

bool Student::getIsFullTime() const {
    return isFullTime;
}

QString Student::getMajor() const {
    return major;
}
