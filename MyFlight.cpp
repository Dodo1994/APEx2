
#include "MyFlight.h"
#include "IDCreator.h"

int MyFlight::getModelNumber() {
    return this->model_number;
}

list<Reservation *> MyFlight::getReservations() {
    return this->myReservations;
}

list<Employee *> MyFlight::getAssignedCrew() {
    return this->myCrew;
}

Date MyFlight::getDate() {
    return this->date;
}

string MyFlight::getSource() {
    return this->source;
}

string MyFlight::getDestination() {
    return this->destination;
}

MyFlight::~MyFlight() = default;

MyFlight::MyFlight(int model_number, Date date, string source, string destination) {
    // to know according to id which class it is
    this->id = 'F' + IDCreator::create(false);
    this->model_number = model_number;
    this->date = date;
    this->source = source;
    this->destination = destination;
}

MyFlight::MyFlight(string id, int model_number, Date date, string source, string destination) {
    this->id = id;
    this->model_number = model_number;
    this->date = date;
    this->source = source;
    this->destination = destination;
}

string MyFlight::getID() {
    return this->id;
}

void MyFlight::addReservations(Reservation *res) {
    this->myReservations.push_back(res);
}

void MyFlight::addCrew(MyEmployee *pEmployee) {
    this->myCrew.push_back(pEmployee);
}
