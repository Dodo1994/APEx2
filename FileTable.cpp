//
// Created by doviwid on 11/26/18.
//


#include "FileTable.h"

void FileTable::loadFile(string fileName, MyImplementation *ex2) {
    ifstream file(fileName);
    // Check error.
    if (file.fail()) {
        return;
    }
    char type = fileName[0];
    while (!file.eof()) {
        if (type == 'E') {
            string id, employerId;
            int seniorty, birthYear;
            char c;
            Jobs title;
            file >> id >> seniorty >> birthYear >> employerId >> c;
            if (c == 'M') {
                title = MANAGER;
            } else if (c == 'P') {
                title = PILOT;
            } else if (c == 'F') {
                title = FLY_ATTENDANT;
            } else if (c == 'N') {
                title = NAVIGATOR;
            } else if (c == 'O') {
                title = OTHER;
            }
            if (employerId == "-") {
                employerId = "";
            }
            if (!id.empty()) {
                ex2->addEmployee(id, seniorty, birthYear, employerId, title);
            }
        }
            // Plane file.
        else if (type == 'P') {
            string id;
            int modelNumber, manager, navigator, flightAttendant, pilot, other, firstClass, secondClass;

            file >> id >> modelNumber >> manager >> navigator >> flightAttendant >> pilot >> other >> firstClass
                 >> secondClass;
            map<Jobs, int> crewNeeded;
            map<Classes, int> maxPassangers;
            crewNeeded[MANAGER] = manager;
            crewNeeded[FLY_ATTENDANT] = flightAttendant;
            crewNeeded[PILOT] = pilot;
            crewNeeded[OTHER] = other;
            crewNeeded[NAVIGATOR] = navigator;
            maxPassangers[FIRST_CLASS] = firstClass;
            maxPassangers[SECOND_CLASS] = secondClass;
            if (!id.empty()) {
                ex2->addPlane(id, modelNumber, crewNeeded, maxPassangers);
            }

        }
            // Flight file.
        else if (type == 'F') {
            string id, date, source, destination;
            int modelNumber;
            file >> id >> modelNumber >> date >> source >> destination;
            if (!id.empty()) {
                ex2->addFlight(id, modelNumber, date, source, destination);
            }
        }
            // Customer file.
        else if (type == 'C') {
            string id, firstName, lastName;
            int priority;
            file >> id >> firstName >> lastName >> priority;
            string fullName = firstName + " " + lastName;
            if (!id.empty()) {
                ex2->addCustomer(id, fullName, priority);
            }
        }
            // Reservation file.
        else if (type == 'R') {
            string id, customerId, flightId;
            int maxBag;
            char cls;
            Classes clas;
            file >> id >> customerId >> flightId >> cls >> maxBag;
            if (cls == 'F') {
                clas = FIRST_CLASS;
            } else if (cls == 'S') {
                clas = SECOND_CLASS;
            }
            if (!(id.empty() || customerId.empty() || flightId.empty())) {
                ex2->addResevation(id, customerId, flightId, clas, maxBag);
            }
        }
            // Working employees file.
        else if (type == 'W') {
            string idEmp, idFli;
            file >> idEmp >> idFli;
            if (!(idEmp.empty() || idFli.empty())) {
                ex2->setFlightsByCrew(idEmp, idFli);
            }
        }
    }
    file.close();
}

void FileTable::saveEmployeeFile(map<string, MyEmployee *> employees) {
    ofstream file("Employees.txt", ios::trunc);
    if (file.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    char jb;
    for (auto &employee: employees) {
        Jobs job = employee.second->getTitle();
        if (job == MANAGER) {
            jb = 'M';
        } else if (job == PILOT) {
            jb = 'P';
        } else if (job == FLY_ATTENDANT) {
            jb = 'F';
        } else if (job == NAVIGATOR) {
            jb = 'N';
        } else if (job == OTHER) {
            jb = 'O';
        }
        string employer;
        if (employee.second->getEmployer() == nullptr) {
            employer = "-";
        } else {
            employer = employee.second->getEmployer()->getID();
        }
        file << employee.second->getID() << ' ' << employee.second->getSeniority() << ' '
             << employee.second->getBirthYear()
             << ' ' << employer << ' ' << jb << endl;
    }

    file.close();
}

void FileTable::savePlaneFile(map<string, MyPlane *> planes) {
    ofstream file("Planes.txt");
    if (file.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    for (auto &plane: planes) {
        file << plane.second->getID() << ' ' << plane.second->getModelNumber() << ' '
             << plane.second->getCrewNeeded()[MANAGER] << ' ' << plane.second->getCrewNeeded()[NAVIGATOR] << ' '
             << plane.second->getCrewNeeded()[FLY_ATTENDANT] << ' ' << plane.second->getCrewNeeded()[PILOT]
             << ' '
             << plane.second->getCrewNeeded()[OTHER] << ' ' << plane.second->getMaxFirstClass() << ' '
             << plane.second->getMaxEconomyClass() << endl;
    }
    file.close();
}

void FileTable::saveFlightFile(map<string, MyFlight *> flights) {
    ofstream file("Flights.txt");
    if (file.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    for (auto &flight: flights) {
        file << flight.second->getID() << ' ' << flight.second->getModelNumber() << ' '
             << flight.second->getDate().getDate() << ' ' << flight.second->getSource() << ' '
             << flight.second->getDestination() << endl;
    }
    file.close();
}

void FileTable::saveCustomerFile(map<string, MyCustomer *> customers) {
    ofstream file("Customers.txt");
    if (file.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    for (auto &customer: customers) {
        file << customer.second->getID() << ' ' << customer.second->getFullName() << ' '
             << customer.second->getPriority()
             << endl;
    }
    file.close();
}

void FileTable::saveReservationFile(map<string, MyReservation *> reservations) {
    ofstream file("Reservations.txt");
    if (file.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    Classes clas;
    char c;
    for (auto &reservation: reservations) {
        clas = reservation.second->getClass();
        if (clas == FIRST_CLASS) {
            c = 'F';
        } else if (clas == SECOND_CLASS) {
            c = 'S';
        }
        file << reservation.second->getID() << ' ' << reservation.second->getCustomer()->getID() << ' '
             << reservation.second->getFlight()->getID() << ' ' << c << ' '
             << reservation.second->getMaxBaggage() << endl;
    }
    file.close();
}

void FileTable::saveEmployeeFlightFile(map<string, string> employees) {
    ofstream file("Working.txt");
    if (file.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    for (auto &employee: employees) {
        file << employee.first << ' ' << employee.second << endl;
    }
    file.close();
}
