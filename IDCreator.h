

#ifndef APEX2_IDCREATOR_H
#define APEX2_IDCREATOR_H

#include <string>
#include <ios>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class IDCreator {
public:
    static string create(bool save);
    static unsigned long loadCount();

private:
    IDCreator();
};


#endif //APEX2_IDCREATOR_H
