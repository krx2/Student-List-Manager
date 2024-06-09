#include "Human.h"

Human::Human(const QString& firstName, const QString& lastName)
    : firstName(firstName), lastName(lastName) {}

QString Human::getFirstName() const {
    return firstName;
}

QString Human::getLastName() const {
    return lastName;
}

QString Human::getFullName() const {
    return firstName + " " + lastName;
}
