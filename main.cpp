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
    Employee* e16 = ex2->addEmployee(7, 1906, "", PILOT);
    Employee* e17 = ex2->addEmployee(7, 1907, "", PILOT);


    Customer* c1 = ex2->addCustomer("ori d", 3);

    map<Jobs, int> crew1,crew2;
    crew2.insert(std::pair<Jobs, int>(MANAGER, 1));
    crew2.insert(std::pair<Jobs, int>(NAVIGATOR, 1));
    crew2.insert(std::pair<Jobs, int>(PILOT, 2));

    map<Classes, int> clas1,clas2;
    clas1.insert(std::pair<Classes, int>(FIRST_CLASS, 12));
    clas1.insert(std::pair<Classes, int>(SECOND_CLASS, 4));

    Plane* p5 = ex2->addPlane(975, crew2, clas1);

    Flight* f1 = ex2->addFlight(975, Date("2018-11-25"), "israel", "usa");

    Reservation* r1 = ex2->addResevation(c1->getID(), f1->getID(), FIRST_CLASS, 2);
    ex2->exit();
    delete ex2;
    return 0;
}