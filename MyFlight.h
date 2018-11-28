
#ifndef APEX2_MYFLIGHT_H
#define APEX2_MYFLIGHT_H

#include "interface.h"
#include "MyEmployee.h"


class MyFlight : public Flight {
    string id;
    int model_number;
    Date date = Date("");
    list<Reservation *> myReservations;
    list<Employee *> myCrew;
    string source;
    string destination;


public:
    MyFlight(int model_number, Date date, string source, string destination);

    MyFlight(string id, int model_number, Date date, string source, string destination);

    void addReservations(Reservation* res);

    int getModelNumber();

    list<Reservation *> getReservations();

    list<Employee *> getAssignedCrew();

    Date getDate();

    string getSource();

    string getDestination();

    string getID();

    ~MyFlight();

    void addCrew(MyEmployee *employee);
};


#endif //APEX2_MYFLIGHT_H
