//
// Created by doviwid on 11/25/18.
//

#ifndef APEX2_MYIMPLEMENTATION_H
#define APEX2_MYIMPLEMENTATION_H

#include "interface.h"
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyCustomer.h"
#include "MyReservation.h"

class MyImplementation : public Ex2 {
private:
    bool empFile = true;
    bool plaFile = true;
    bool fliFile = true;
    bool cusFile = true;
    bool resFile = true;
    map<string, MyEmployee *> employees;
    map<string, MyPlane *> planes;
    map<int, MyPlane *> planesByModel;
    map<string, MyFlight *> flights;
    map<string, MyCustomer *> customers;
    map<string, MyReservation *> reservations;

public:
    MyImplementation() = default;

    Employee *addEmployee(
            int seniority,
            int birth_year,
            string employer_id,
            Jobs title);

    Employee *addEmployee(string id,
                          int seniority,
                          int birth_year,
                          string employer_id,
                          Jobs title);

    Employee *getEmployee(string id);

    Plane *addPlane(
            int model_number,
            map<Jobs, int> crew_needed,
            map<Classes, int> max_passangers);

    Plane *addPlane(string id,
                    int model_number,
                    map<Jobs, int> crew_needed,
                    map<Classes, int> max_passangers);

    Plane *getPlane(string id);

    Flight *addFlight(
            int model_number,
            Date date,
            string source,
            string destination);

    Flight *addFlight(string id,
                      int model_number,
                      Date date,
                      string source,
                      string destination);


    Flight *getFlight(string id);

    Customer *addCustomer(
            string full_name,
            int priority);

    Customer *addCustomer(string id,
                          string full_name,
                          int priority);

    Customer *getCustomer(string id);

    Reservation *addResevation(
            string customerId,
            string flightId,
            Classes cls,
            int max_baggage);

    Reservation *addResevation(string id,
                               string customerId,
                               string flightId,
                               Classes cls,
                               int max_baggage);

    Reservation *getReservation(string id);

    int getNumberOfPassangers(string flight);

    bool loadIfWorkingEmployee(string employee, Date date);

    void saveWorking(string key, string value);

    bool loadIfUsedPlane(string plane, Date date);

    void loadFlightCrew(MyFlight* flight);

    template<class T>
    void deleteMaps(map<string, T> myMap) {
        for (auto &mymap: myMap) {
            delete mymap.second;
        }
    }

    void exit();

    ~MyImplementation();
};

#endif //APEX2_MYIMPLEMENTATION_H
