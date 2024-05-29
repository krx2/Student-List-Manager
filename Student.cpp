#include "Student.h"

Student::Student(const QString& firstName, const QString& lastName)
    : firstName(firstName), lastName(lastName) {}

QString Student::getFirstName() const {
    return firstName;
}

QString Student::getLastName() const {
    return lastName;
}

QString Student::getFullName() const {
    return firstName + " " + lastName;
}
