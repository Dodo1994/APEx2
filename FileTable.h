

#ifndef APEX2_FILETABLE_H
#define APEX2_FILETABLE_H

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include "interface.h"
#include "MyPlane.h"
#include "MyReservation.h"
#include "MyFlight.h"
#include "MyCustomer.h"
#include "MyEmployee.h"
#include "MyImplementation.h"

using namespace std;

class FileTable {
    FileTable() = default;

public:
    static void saveEmployeeFile(map<string, MyEmployee *> employees);

    static void savePlaneFile(map<string, MyPlane *> planes);

    static void saveFlightFile(map<string, MyFlight *> flights);

    static void saveCustomerFile(map<string, MyCustomer *> customers);

    static void saveReservationFile(map<string, MyReservation *> reservations);

    static void loadFile(string fileName, MyImplementation *ex2);

    static string swapChars(string word, char a , char b);
};


#endif //APEX2_FILETABLE_H
