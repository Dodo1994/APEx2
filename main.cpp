#include "interface.h"
#include "MyImplementation.h"

#include <iostream>

int main()
{
    Ex2* ex2 = new MyImplementation();  // This line must work!

    Employee* e1 = ex2->addEmployee(4, 1994, "", MANAGER);
    Employee* e2 = ex2->addEmployee(4, 1974, e1->getID(), PILOT);
    Employee* e3 = ex2->addEmployee(5, 1850, "", FLY_ATTENDANT);
    Employee* e4 = ex2->addEmployee(7, 1950, "", PILOT);
    Employee* e5 = ex2->addEmployee(4, 1840, "", FLY_ATTENDANT);
    Employee* e6 = ex2->addEmployee(10, 1999, "", NAVIGATOR);
    Employee* e7 = ex2->addEmployee(19, 2019, "", NAVIGATOR);
    Employee* e8 = ex2->addEmployee(5, 1995, e2->getID(), MANAGER);
    Employee* e9 = ex2->addEmployee(6, 1996, e1->getID(), MANAGER);
    Employee* e10 = ex2->addEmployee(7, 1997, "", MANAGER);
    Employee* e11 = ex2->addEmployee(7, 1901, "", MANAGER);
    Employee* e12 = ex2->addEmployee(7, 1902, "", MANAGER);
    Employee* e13 = ex2->addEmployee(7, 1903, "", NAVIGATOR);
    Employee* e14 = ex2->addEmployee(7, 1904, "", NAVIGATOR);
    Employee* e15 = ex2->addEmployee(7, 1905, "", NAVIGATOR);
    Employee* e16 = ex2->addEmployee(7, 1906, "", PILOT);
    Employee* e17 = ex2->addEmployee(7, 1907, "", PILOT);
    Employee* e18 = ex2->addEmployee(7, 1911, "", PILOT);
    Employee* e19 = ex2->addEmployee(7, 1912, e2->getID(), PILOT);
    Employee* e20 = ex2->addEmployee(7, 1913, e2->getID(), PILOT);
    Employee* e21 = ex2->addEmployee(7, 1914, e3->getID(), PILOT);
    Employee* e22 = ex2->addEmployee(7, 1915, e4->getID(), PILOT);
    Employee* e23 = ex2->addEmployee(7, 1916, e5->getID(), PILOT);
    Employee* e24 = ex2->addEmployee(7, 1917, e6->getID(), PILOT);


    Customer* c1 = ex2->addCustomer("ori d", 3);
    Customer* c2 = ex2->addCustomer("orr di", 5);
    Customer* c3 = ex2->addCustomer("ori dri", 6);
    Customer* c4 = ex2->addCustomer("roi d", 1);
    Customer* c5 = ex2->addCustomer("roi d2", 6);
    Customer* c6 = ex2->addCustomer("ori ori", 6);

    map<Jobs, int> crew1,crew2;
    crew1.insert(std::pair<Jobs, int>(MANAGER, 0));
    crew1.insert(std::pair<Jobs, int>(NAVIGATOR, 1));
    crew1.insert(std::pair<Jobs, int>(PILOT, 0));
    crew2.insert(std::pair<Jobs, int>(MANAGER, 1));
    crew2.insert(std::pair<Jobs, int>(NAVIGATOR, 1));
    crew2.insert(std::pair<Jobs, int>(PILOT, 2));

    map<Classes, int> clas1,clas2;
    clas1.insert(std::pair<Classes, int>(FIRST_CLASS, 12));
    clas1.insert(std::pair<Classes, int>(SECOND_CLASS, 4));
    clas2.insert(std::pair<Classes, int>(FIRST_CLASS, 20));
    clas2.insert(std::pair<Classes, int>(SECOND_CLASS, 20));

    Plane* p1 = ex2->addPlane(125, crew1, clas1);
    Plane* p2 = ex2->addPlane(125, crew1, clas1);
    Plane* p3 = ex2->addPlane(995, crew1, clas2);
    Plane* p4 = ex2->addPlane(885, crew1, clas2);
    Plane* p5 = ex2->addPlane(975, crew2, clas1);
    Plane* p6 = ex2->addPlane(605, crew2, clas2);
    Plane* p7 = ex2->addPlane(605, crew2, clas1);

    Flight* f1 = ex2->addFlight(975, Date("2018-11-25"), "israel", "usa");
    Flight* f2 = ex2->addFlight(125, Date("2019-01-25"), "Poland", "greece");
    Flight* f3 = ex2->addFlight(125, Date("2019-01-26"), "USA", "greece");
    Flight* f4 = ex2->addFlight(885, Date("2019-02-02"), "london", "israel");
    Flight* f5 = ex2->addFlight(605, Date("2019-01-17"), "Poland", "berlin");
    Flight* f6 = ex2->addFlight(605, Date("2019-01-13"), "Poland", "berlin");

    Reservation* r1 = ex2->addResevation(c1->getID(), f1->getID(), FIRST_CLASS, 2);
    Reservation* r2 = ex2->addResevation(c2->getID(), f1->getID(), FIRST_CLASS, 2);
    Reservation* r3 = ex2->addResevation(c1->getID(), f2->getID(), SECOND_CLASS, 2);
    Reservation* r4 = ex2->addResevation(c3->getID(), f2->getID(), FIRST_CLASS, 2);
    Reservation* r5 = ex2->addResevation(c4->getID(), f3->getID(), FIRST_CLASS, 2);
    Reservation* r7 = ex2->addResevation(c1->getID(), f4->getID(), SECOND_CLASS, 2);
    Reservation* r8 = ex2->addResevation(c6->getID(), f5->getID(), FIRST_CLASS, 2);

    ex2->exit();
    delete ex2;
    return 0;
}