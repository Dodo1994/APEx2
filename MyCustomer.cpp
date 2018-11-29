
#include "IDCreator.h"
#include "MyCustomer.h"

MyCustomer::MyCustomer(string name, int importance) {
    this->id = 'C' + IDCreator::create(false);
    this->fullName = name;
    this->importance = importance;
}

MyCustomer::MyCustomer(string id, string name, int importance) {
    this->id = id;
    this->fullName = name;
    this->importance = importance;
}

void MyCustomer::addReservations(Reservation* res) {
    this->myResevations.push_back(res);
}

string MyCustomer::getFullName() {
    return this->fullName;
}

int MyCustomer::getPriority() {
    return this->importance;
}

list<Reservation *> MyCustomer::getReservations() {
    return this->myResevations;
}

string MyCustomer::getID() {
    return this->id;
}

MyCustomer::~MyCustomer() = default;
