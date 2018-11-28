
#ifndef APEX2_MYRESERVATION_H
#define APEX2_MYRESERVATION_H

#include "interface.h"

class MyReservation : public Reservation {
    string id;
    Customer *customer;
    Flight *flight;
    Classes clas;
    int maxBaggage;

public:
    MyReservation(Customer *customer, Flight *flight, Classes clas, int maxBaggage);

    MyReservation(string id, Customer *customer, Flight *flight, Classes clas, int maxBaggage);

    Customer *getCustomer();

    Flight *getFlight();

    Classes getClass();

    virtual int getMaxBaggage();

    string getID();

    ~MyReservation();
};

#endif //APEX2_MYRESERVATION_H
