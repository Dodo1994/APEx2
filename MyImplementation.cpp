

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
        if (this->employees.count(employer_id) == 0) {
            throw "Employer ID mismatch";
            return nullptr;
        }
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
    if (empFile) {
        FileTable::loadFile("Employees.txt", this);
        empFile = false;
    }
    MyPlane *temp = this->planesByModel[model_number];
    if (temp == nullptr) {
        throw "No available planes";
    }
    auto *flight = new MyFlight(model_number, date, source, destination);
    int man = temp->getCrewNeeded()[MANAGER];
    int pil = temp->getCrewNeeded()[PILOT];
    int att = temp->getCrewNeeded()[FLY_ATTENDANT];
    int nav = temp->getCrewNeeded()[NAVIGATOR];
    int oth = temp->getCrewNeeded()[OTHER];
    string myId;
    for (auto &employee: this->employees) {
        bool isWorking = false;
        if (this->loadIfWorkingEmployee(employee.first, flight)) {
            isWorking = true;
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
        delete flight;
        throw "Missing crew members";
    }
    bool foundPlane = false;
    for (auto &pla: this->planes) {
        if (pla.second->getModelNumber() == model_number) {
            if (!(this->loadIfUsedPlane(pla.first, date))) {
                this->saveWorking(flight->getID(), pla.first);
                foundPlane = true;
            }
        }
    }
    if (!foundPlane) {
        delete flight;
        throw "No available planes";
    }
    for (auto &crew: flight->getAssignedCrew()) {
        this->saveWorking(crew->getID(), flight->getID());
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
    if (empFile) {
        FileTable::loadFile("Employees.txt", this);
        empFile = false;
    }
    auto *flight = new MyFlight(id, model_number, date, source, destination);
    this->loadFlightCrew(flight);
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
    if (priority > 5 || priority < 0) {
        throw "Priority number error";
    }
    if (cusFile) {
        FileTable::loadFile("Customers.txt", this);
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
        FileTable::loadFile("Customers.txt", this);
        cusFile = false;
    }
    if (this->customers.count(id) == 0) {
        return nullptr;
    }
    return this->customers[id];
}

Reservation *
MyImplementation::addResevation(string id, string customerId, string flightId, Classes cls, int max_baggage) {
    if (cusFile) {
        FileTable::loadFile("Customers.txt", this);
        cusFile = false;
    }
    if (fliFile) {
        FileTable::loadFile("Flights.txt", this);
        fliFile = false;
    }
    if (this->customers.count(customerId) == 0) {
        return nullptr;
    }
    if (this->flights.count(flightId) == 0) {
        return nullptr;
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
        FileTable::loadFile("Reservations.txt", this);
        resFile = false;
    }
    if (cusFile) {
        FileTable::loadFile("Customers.txt", this);
        cusFile = false;
    }
    if (fliFile) {
        FileTable::loadFile("Flights.txt", this);
        fliFile = false;
    }
    if (this->customers.count(customerId) == 0) {
        throw "No such customer";
    }
    if (this->flights.count(flightId) == 0) {
        throw "No such flight";
    }
    if (cls == FIRST_CLASS) {
        if (this->getNumberOfPassangers(flightId) >=
            this->planesByModel[getFlight(flightId)->getModelNumber()]->getMaxFirstClass()) {
            throw "First class is full";
        }
    } else {
        if (this->getNumberOfPassangers(flightId) >=
            this->planesByModel[getFlight(flightId)->getModelNumber()]->getMaxEconomyClass()) {
            throw "Economy class is full";
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
        FileTable::loadFile("Reservations.txt", this);
        resFile = false;
    }
    if (this->reservations.count(id) == 0) {
        return nullptr;
    }
    return this->reservations[id];
}

void MyImplementation::exit() {
    if (empFile) {
        FileTable::loadFile("Employees.txt", this);
        empFile = false;
    }
    if (plaFile) {
        FileTable::loadFile("Planes.txt", this);
        plaFile = false;
    }
    if (fliFile) {
        FileTable::loadFile("Flights.txt", this);
        fliFile = false;
    }
    if (resFile) {
        FileTable::loadFile("Reservations.txt", this);
        resFile = false;
    }
    if (cusFile) {
        FileTable::loadFile("Customers.txt", this);
        cusFile = false;
    }
    FileTable::saveEmployeeFile(this->employees);
    FileTable::savePlaneFile(this->planes);
    FileTable::saveCustomerFile(this->customers);
    FileTable::saveFlightFile(this->flights);
    FileTable::saveReservationFile(this->reservations);
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


int MyImplementation::getNumberOfPassangers(string flight) {
    int count = 0;
    for (auto &res: this->reservations) {
        if (res.second->getFlight()->getID() == flight) {
            count++;
        }
    }
    return count;
}

bool MyImplementation::loadIfWorkingEmployee(string employee, MyFlight *flight) {
    ifstream file("Working.txt");
    // Check error.
    if (file.fail()) {
        return false;
    }
    while (!file.eof()) {
        string idEmp, idFli;
        file >> idEmp >> idFli;
        if (!(idEmp.empty() || idFli.empty())) {
            if (idEmp == employee) {
                if (this->flights[idFli]->getDate() == flight->getDate() && idFli != flight->getID()) {
                    file.close();
                    return true;
                }
            }
        }
    }
    file.close();
    return false;
}

void MyImplementation::saveWorking(string key, string value) {
    ofstream file("Working.txt", ios::app);
    if (file.fail()) {
        throw "Error opening file";
    }
    file << key << ' ' << value << endl;
    file.close();
}

bool MyImplementation::loadIfUsedPlane(string plane, Date date) {
    ifstream file("Working.txt");
    // Check error.
    if (file.fail()) {
        return false;
    }
    while (!file.eof()) {
        string idFli, idPla;
        file >> idFli >> idPla;
        if (!(idFli.empty() || idPla.empty())) {
            if (idPla == plane) {
                if (this->flights[idFli]->getDate() == date) {
                    file.close();
                    return true;
                }
            }
        }
    }
    file.close();
    return false;
}

void MyImplementation::loadFlightCrew(MyFlight *flight) {
    ifstream file("Working.txt");
    // Check error.
    if (file.fail()) {
        return;
    }
    while (!file.eof()) {
        string idEmp, idFli;
        file >> idEmp >> idFli;
        if (!(idFli.empty() || idEmp.empty())) {
            if (idFli == flight->getID()) {
                flight->addCrew(this->employees[idEmp]);
            }
        }
    }
    file.close();
}
