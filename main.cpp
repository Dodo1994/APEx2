#include "interface.h"
#include "MyImplementation.h"

#include <iostream>

int main()
{
    Ex2 *my = new MyImplementation();  // This line must work!

    Employee* e1 = my->addEmployee(2, 1994, "", MANAGER);
    Employee* e2 = my->addEmployee(2, 1914, "", MANAGER);
    Employee* e3 = my->addEmployee(2, 1094, "", MANAGER);
    Employee* e4 = my->addEmployee(2, 1900, "", MANAGER);
    Employee* e5 = my->addEmployee(3, 1994, e4->getID(), MANAGER);
    Employee* e6 = my->addEmployee(4, 1974, e4->getID(), PILOT);
    Employee* e7 = my->addEmployee(5, 1850, e4->getID(), FLY_ATTENDANT);
    Employee* e8 = my->addEmployee(7, 1950, e3->getID(), PILOT);
    Employee* e9 = my->addEmployee(1, 1840, e3->getID(), FLY_ATTENDANT);
    Employee* e10 = my->addEmployee(0, 1999, e7->getID(), NAVIGATOR);
    Employee* e11 = my->addEmployee(19, 2019, e8->getID(), NAVIGATOR);

    map<Jobs, int> crew;
    crew.insert(std::pair<Jobs, int>(MANAGER, 2));
    crew.insert(std::pair<Jobs, int>(NAVIGATOR, 1));
    crew.insert(std::pair<Jobs, int>(PILOT, 1));
    map<Classes, int> classSeats;
    classSeats.insert(std::pair<Classes, int>(FIRST_CLASS, 2));
    classSeats.insert(std::pair<Classes, int>(SECOND_CLASS, 2));
    Plane* p1 = my->addPlane(123, crew, classSeats);
    Plane* p2 = my->addPlane(153, crew, classSeats);
    Plane* p3 = my->addPlane(3333, crew, classSeats);
    Plane* p4 = my->addPlane(993, crew, classSeats);
    Plane* p5 = my->addPlane(3363, crew, classSeats);
    Plane* p6 = my->addPlane(1113, crew, classSeats);

    Customer* c1 = my->addCustomer("ori kopel", 3);
    Customer* c2 = my->addCustomer("shlomo gt", 5);
    Customer* c3 = my->addCustomer("moshe bg", 6);
    Customer* c4 = my->addCustomer("dowi", 1);
    Customer* c5 = my->addCustomer("renana th", 6);
    Customer* c6 = my->addCustomer("nushnushit thtf", 6);

    Flight* f1 = my->addFlight(123, Date("2018-11-25"), "israel", "los angeles");
    Flight* f2 = my->addFlight(153, Date("2019-01-25"), "Poland", "greece");
    Flight* f3 = my->addFlight(3333, Date("2019-01-26"), "USA", "greece");
    Flight* f4 = my->addFlight(153, Date("2019-02-02"), "london", "israel");
    Flight* f5 = my->addFlight(993, Date("2019-01-13"), "Poland", "berlin");
    Flight* f6 = my->addFlight(1113, Date("2019-01-13"), "Poland", "berlin");
    Reservation* r1 = my->addResevation(c1->getID(), f1->getID(), FIRST_CLASS, 2);
    Reservation* r2 = my->addResevation(c1->getID(), f1->getID(), FIRST_CLASS, 2);

    my->exit();
    delete my;

    Ex2 *my2 = new MyImplementation();
    Customer* c = my2->addCustomer("kok", 99);
    Employee* e = my2->addEmployee(5, 2020, "", PILOT);
    Plane* p = my2->addPlane(23, crew, classSeats);
    Flight* f = my2->addFlight(3333, Date("2014-05-08"), "givaat shmuel A", "ze good yaaad");
    Reservation* r = my2->addResevation(c->getID(), f->getID(), SECOND_CLASS, 1);

    my2->exit();
    delete my2;
    return 0;
}