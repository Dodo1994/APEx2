
#ifndef APEX2_MYPLANE_H
#define APEX2_MYPLANE_H

#include "interface.h"

class MyPlane : public Plane {
    string id;
    int modelNumber;
    map<Jobs, int> crewNeeded;
    map<Classes, int> maxPassangers;

public:
    MyPlane(string id, int model_number, map<Jobs, int> crewNeeded, map<Classes, int> maxPassangers);

    MyPlane(int model_number, map<Jobs, int> crewNeeded, map<Classes, int> maxPassangers);

    string getID();

    int getModelNumber();

    map<Jobs, int> getCrewNeeded();

    int getMaxFirstClass();

    int getMaxEconomyClass();

    virtual ~MyPlane();
};


#endif //APEX2_MYPLANE_H
