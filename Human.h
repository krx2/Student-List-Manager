#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include <QString>

class Human {
public:
    Human(const QString& firstName, const QString& lastName);

    QString getFirstName() const;
    QString getLastName() const;
    QString getFullName() const;

private:
    QString firstName;
    QString lastName;
};

#endif // HUMAN_H
