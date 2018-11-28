
#include "IDCreator.h"
#include "MyEmployee.h"


int MyEmployee::getBirthYear() {
    return this->birthYear;
}

Employee *MyEmployee::getEmployer() {
    return this->employer;
}

string MyEmployee::getID() {
    return this->id;
}

int MyEmployee::getSeniority() {
    return this->seniority;
}

Jobs MyEmployee::getTitle() {
    return this->title;
}

MyEmployee::MyEmployee(string id, int seniority, int birthYear, Jobs title, Employee *employer) {
    this->seniority = seniority;
    this->birthYear = birthYear;
    this->employer = employer;
    this->title = title;
    this->id = id;
}

MyEmployee::~MyEmployee() = default;

MyEmployee::MyEmployee(int seniority, int birthYear, Jobs title, Employee *employer) {
    this->seniority = seniority;
    this->birthYear = birthYear;
    this->employer = employer;
    this->title = title;
    // to know according to id which class it is
    this->id = 'E' + IDCreator::create(false);
}