
#include "MyImplementation.h"
#include "FileTable.h"
#include "IDCreator.h"
#include <iostream>


Employee *MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    if (empFile) {
        FileTable::loadFile("Employees.txt", this);
        empFile = false;
    }
    MyEmployee *emp;
    if (!employer_id.empty()) {
        emp = new MyEmployee(seniority, birth_year, title, this->employees[employer_id]);
    } else {
        emp = new MyEmployee(seniority, birth_year, title, nullptr);
    }
    this->employees[emp->getID()] = emp;
    cout << "Added employee successfully" << endl;
    return emp;
}

Employee *MyImplementation::addEmployee(string id, int seniority, int birth_year, string employer_id, Jobs title) {
    MyEmployee *emp;
    if (!employer_id.empty()) {
        emp = new MyEmployee(id, seniority, birth_year, title, this->employees[employer_id]);
    } else {
        emp = new MyEmployee(id, seniority, birth_year, title, nullptr);
    }
    this->employees[emp->getID()] = emp;
    return emp;
}

Employee *MyImplementation::getEmployee(string id) {
    if (empFile) {
        FileTable::loadFile("Employees.txt", this);
        empFile = false;
    }
    if (this->employees.count(id) == 0) {
        return nullptr;
    }
    return this->employees[id];
}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    if (plaFile) {
        FileTable::loadFile("Planes.txt", this);
        plaFile = false;
    }
    auto *plane = new MyPlane(model_number, crew_needed, max_passangers);
    this->planes[plane->getID()] = plane;
    if (this->planesByModel.count(plane->getModelNumber()) == 0) {
        this->planesByModel[plane->getModelNumber()] = plane;
    }
    cout << "Added plane successfully" << endl;
    return plane;
}

Plane *
MyImplementation::addPlane(string id, int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    auto *plane = new MyPlane(id, model_number, crew_needed, max_passangers);
    this->planes[plane->getID()] = plane;
    if (this->planesByModel.count(plane->getModelNumber()) == 0) {
        this->planesByModel[plane->getModelNumber()] = plane;
    }
    return plane;
}

Plane *MyImplementation::getPlane(string id) {
    if (plaFile) {
        FileTable::loadFile("Planes.txt", this);
        plaFile = false;
    }
    if (this->planes.count(id) == 0) {
        return nullptr;
    }
    return this->planes[id];
}

Flight *MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    if (fliFile) {
        FileTable::loadFile("Flights.txt", this);
        fliFile = false;
    }
    if (plaFile) {
        FileTable::loadFile("Planes.txt", this);
        plaFile = false;
    }
    if (worFile) {
        FileTable::loadFile("Working.txt", this);
        worFile = false;
    }
    if (empFile) {
        FileTable::loadFile("Employees.txt", this);
        empFile = false;
    }
    MyPlane *temp = this->planesByModel[model_number];
    auto *flight = new MyFlight(model_number, date, source, destination);
    int man = temp->getCrewNeeded()[MANAGER];
    int pil = temp->getCrewNeeded()[PILOT];
    int att = temp->getCrewNeeded()[FLY_ATTENDANT];
    int nav = temp->getCrewNeeded()[NAVIGATOR];
    int oth = temp->getCrewNeeded()[OTHER];
    string myId;
    for (auto &employee: this->employees) {
        bool isWorking = false;
        if (this->flightsByCrew.count(employee.first) > 0) {
            myId=this->flightsByCrew.find(employee.first)->second;
            if(myId[0]=='F') {
                if (this->flights[myId]->getDate() == flight->getDate()) {
                    isWorking = true;
                }
            }
        }
        if (!isWorking) {
            if (employee.second->getTitle() == MANAGER && man > 0) {
                flight->addCrew(employee.second);
                man--;
            } else if (employee.second->getTitle() == PILOT && pil > 0) {
                flight->addCrew(employee.second);
                pil--;
            } else if (employee.second->getTitle() == FLY_ATTENDANT && att > 0) {
                flight->addCrew(employee.second);
                att--;
            } else if (employee.second->getTitle() == NAVIGATOR && nav > 0) {
                flight->addCrew(employee.second);
                nav--;
            } else if (employee.second->getTitle() == OTHER && oth > 0) {
                flight->addCrew(employee.second);
                oth--;
            }
        }

    }
    if (man > 0 || pil > 0 || att > 0 || nav > 0 || oth > 0) {
        cout << "Missing crew members" << endl;
        delete flight;
        return nullptr;
    }
    for (auto &pla: this->planes) {
        bool taken = false;
        if (pla.second->getModelNumber() == model_number) {
            for (auto &exist: this->flightsByCrew) {
                if (pla.second->getID() == exist.second) {
                    if (this->getFlight(exist.first)->getDate() == date) {
                        taken = true;
                        break;
                    }
                }
            }
            if (!taken) {
                this->flightsByCrew.insert(pair<string, string>(flight->getID(), pla.first));
            }
        }
    }
    if (this->flightsByCrew.count(flight->getID()) == 0) {
        cout << "No available planes" << endl;
        delete flight;
        return nullptr;
    }
    for (auto &crew: flight->getAssignedCrew()) {
        this->flightsByCrew.insert(pair<string, string>(crew->getID(), flight->getID()));
    }
    this->flights[flight->getID()] = flight;
    cout << "Added flight successfully" << endl;
    return flight;
}

Flight *MyImplementation::addFlight(string id, int model_number, Date date, string source, string destination) {
    if (plaFile) {
        FileTable::loadFile("Planes.txt", this);
        plaFile = false;
    }
    if (worFile) {
        FileTable::loadFile("Working.txt", this);
        worFile = false;
    }
    if (empFile) {
        FileTable::loadFile("Employees.txt", this);
        empFile = false;
    }
    auto *flight = new MyFlight(id, model_number, date, source, destination);
    for (auto &crew: this->flightsByCrew) {
        if (crew.second == flight->getID()) {
            flight->addCrew(this->employees[crew.first]);
        }
    }
    this->flights[flight->getID()] = flight;
    return flight;
}

Flight *MyImplementation::getFlight(string id) {
    if (fliFile) {
        FileTable::loadFile("Flights.txt", this);
        fliFile = false;
    }
    if (this->flights.count(id) == 0) {
        return nullptr;
    }
    return this->flights[id];
}

Customer *MyImplementation::addCustomer(string full_name, int priority) {
    if (cusFile) {
        FileTable::loadFile("Customer.txt", this);
        cusFile = false;
    }
    auto *customer = new MyCustomer(full_name, priority);
    this->customers[customer->getID()] = customer;
    cout << "Added customer successfully" << endl;
    return customer;
}

Customer *MyImplementation::addCustomer(string id, string full_name, int priority) {
    auto *customer = new MyCustomer(id, full_name, priority);
    this->customers[customer->getID()] = customer;
    return customer;
}

Customer *MyImplementation::getCustomer(string id) {
    if (cusFile) {
        FileTable::loadFile("Customer.txt", this);
        cusFile = false;
    }
    if (this->customers.count(id) == 0) {
        return nullptr;
    }
    return this->customers[id];
}

Reservation *
MyImplementation::addResevation(string id, string customerId, string flightId, Classes cls, int max_baggage) {
    if (this->customers.count(customerId) == 0) {
        return nullptr;
    }
    if (this->flights.count(flightId) == 0) {
        return nullptr;
    }
    if (cusFile) {
        FileTable::loadFile("Customer.txt", this);
        cusFile = false;
    }
    if (fliFile) {
        FileTable::loadFile("Flights.txt", this);
        fliFile = false;
    }
    auto *reservation = new MyReservation(id, this->customers[customerId], this->flights[flightId], cls,
                                          max_baggage);
    this->customers[customerId]->addReservations(reservation);
    this->flights[flightId]->addReservations(reservation);
    this->reservations[reservation->getID()] = reservation;
    return reservation;
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    if (resFile) {
        FileTable::loadFile("Resevations.txt", this);
        resFile = false;
    }
    if (cusFile) {
        FileTable::loadFile("Customer.txt", this);
        cusFile = false;
    }
    if (fliFile) {
        FileTable::loadFile("Flights.txt", this);
        fliFile = false;
    }
    if (this->customers.count(customerId) == 0) {
        cout << "No such customer" << endl;
        return nullptr;
    }
    if (this->flights.count(flightId) == 0) {
        cout << "No such flight" << endl;
        return nullptr;
    }
    if (cls == FIRST_CLASS) {
        if (this->getNumberOfPassangers(flightId) >=
            this->planesByModel[getFlight(flightId)->getModelNumber()]->getMaxFirstClass()) {
            cout << "First class is full" << endl;
            return nullptr;
        }
    } else {
        if (this->getNumberOfPassangers(flightId) >=
            this->planesByModel[getFlight(flightId)->getModelNumber()]->getMaxEconomyClass()) {
            cout << "Economy class is full" << endl;
            return nullptr;
        }
    }
    auto *reservation = new MyReservation(this->customers[customerId], this->flights[flightId], cls,
                                          max_baggage);
    this->customers[customerId]->addReservations(reservation);
    this->flights[flightId]->addReservations(reservation);
    this->reservations[reservation->getID()] = reservation;
    cout << "Added reservation successfully" << endl;
    return reservation;
}

Reservation *MyImplementation::getReservation(string id) {
    if (resFile) {
        FileTable::loadFile("Resevations.txt", this);
        resFile = false;
    }
    if (this->reservations.count(id) == 0) {
        return nullptr;
    }
    return this->reservations[id];
}

void MyImplementation::exit() {
    FileTable::saveEmployeeFile(this->employees);
    FileTable::savePlaneFile(this->planes);
    FileTable::saveCustomerFile(this->customers);
    FileTable::saveFlightFile(this->flights);
    FileTable::saveReservationFile(this->reservations);
    FileTable::saveEmployeeFlightFile(this->flightsByCrew);
    IDCreator::create(true);
    cout << "So sad you are leaving!" << endl;
}

MyImplementation::~MyImplementation() {
    this->deleteMaps(this->employees);
    this->deleteMaps(this->planes);
    this->deleteMaps(this->flights);
    this->deleteMaps(this->customers);
    this->deleteMaps(this->reservations);
}

void MyImplementation::setFlightsByCrew(string idEmp, string idFli) {
    this->flightsByCrew.insert(pair<string, string>(idEmp, idFli));
}

int MyImplementation::getNumberOfPassangers(string flight) {
    int count = 0;
    for (auto &res: this->reservations) {
        if (res.second->getFlight()->getID() == flight) {
            count++;
        }
    }
    return count;
}
