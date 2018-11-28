
#ifndef APEX2_MYCUSTOMER_H
#define APEX2_MYCUSTOMER_H

#include "interface.h"


class MyCustomer : public Customer {
    string id;
    string fullName;
    int importance;
    list<Reservation *> myResevations;


public:
    MyCustomer(string id, string name, int importance);

    MyCustomer(string name, int importance);

    void addReservations(Reservation* res);

    string getFullName();

    int getPriority();

    string getID();

    list<Reservation *> getReservations();

    ~MyCustomer();
};


#endif //APEX2_MYCUSTOMER_H
