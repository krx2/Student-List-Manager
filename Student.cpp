#include "Student.h"

Student::Student(const QString& firstName, const QString& lastName, bool isActive, bool isFullTime, const QString& major)
    : firstName(firstName), lastName(lastName), isActive(isActive), isFullTime(isFullTime), major(major) {}

QString Student::getFirstName() const {
    return firstName;
}

QString Student::getLastName() const {
    return lastName;
}

QString Student::getFullName() const {
    return firstName + " " + lastName;
}

bool Student::getIsActive() const {
    return isActive;
}

bool Student::getIsFullTime() const {
    return isFullTime;
}

QString Student::getMajor() const {
    return major;
}
