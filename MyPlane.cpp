
#include "MyPlane.h"
#include "IDCreator.h"

int MyPlane::getModelNumber() {
    return this->modelNumber;
}

map<Jobs, int> MyPlane::getCrewNeeded() {
    return this->crewNeeded;
}

int MyPlane::getMaxFirstClass() {
    return this->maxPassangers.at(FIRST_CLASS);
}

int MyPlane::getMaxEconomyClass() {
    return this->maxPassangers.at(SECOND_CLASS);
}

MyPlane::~MyPlane() = default;

MyPlane::MyPlane(int model_number, map<Jobs, int> crewNeeded, map<Classes, int> maxPassangers) {
    this->modelNumber = model_number;
    this->crewNeeded = crewNeeded;
    this->maxPassangers = maxPassangers;
    // to know according to id which class it is
    this->id = 'P' + IDCreator::create(false);
}

MyPlane::MyPlane(string id, int model_number, map<Jobs, int> crewNeeded, map<Classes, int> maxPassangers) {
    this->modelNumber = model_number;
    this->crewNeeded = crewNeeded;
    this->maxPassangers = maxPassangers;
    this->id = id;
}

string MyPlane::getID() {
    return this->id;
}
