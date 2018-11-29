

#ifndef APEX2_MYEMPLOYEE_H
#define APEX2_MYEMPLOYEE_H

#include "interface.h"

class MyEmployee : public Employee {
    string id;
    int seniority;
    int birthYear;
    Employee *employer;
    Jobs title;

public:
    MyEmployee(string id, int seniority, int birthYear, Jobs title, Employee *employer);

    MyEmployee(int seniority, int birthYear, Jobs title, Employee *employer);

    int getSeniority();

    int getBirthYear();

    Employee *getEmployer();

    Jobs getTitle();

    string getID();

    ~MyEmployee();
};


#endif //APEX2_MYEMPLOYEE_H
