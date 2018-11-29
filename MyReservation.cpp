
#include "MyReservation.h"
#include "IDCreator.h"

Customer *MyReservation::getCustomer() {
    return this->customer;
}

Flight *MyReservation::getFlight() {
    return this->flight;
}

Classes MyReservation::getClass() {
    return this->clas;
}

int MyReservation::getMaxBaggage() {
    return this->maxBaggage;
}

MyReservation::~MyReservation() = default;

string MyReservation::getID() {
    return this->id;
}

MyReservation::MyReservation(Customer *customer, Flight *flight, Classes clas, int maxBaggage) {
    this->id = 'R' + IDCreator::create(false);
    this->customer = customer;
    this->flight = flight;
    this->clas = clas;
    this->maxBaggage = maxBaggage;
}

MyReservation::MyReservation(string id, Customer *customer, Flight *flight, Classes clas, int maxBaggage) {
    this->id = id;
    this->customer = customer;
    this->flight = flight;
    this->clas = clas;
    this->maxBaggage = maxBaggage;
}
