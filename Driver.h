//
// Created by yair on 04/12/16.
//

#ifndef ADPROG1_1_DRIVER_H
#define ADPROG1_1_DRIVER_H

#include <string>
#include "Node.h"
#include "Taxi.h"

using namespace std;

class Driver {
private:
    int id;
    int age;
    int yearsExp;
    bool occupied;
    string status;
    Taxi* taxi = NULL;
    float avgSatisfaction = 0;
    Node* location = NULL;

public:
    Driver(int id, int age, int yearsExp, string status);

    int getId();

    void setId(int id);

    int getAge();

    void setAge(int age);

    int getYearsExp();

    void setYearsExp(int yearsExp);

    bool isOccupied();

    void setOccupied(bool occupied);

    const string &getStatus();

    void setStatus(string status);

    Taxi *getTaxi();

    void setTaxi(Taxi *taxi);

    float getAvgSatisfaction();

    void setAvgSatisfaction(float avgSatisfaction);

    Node *getLocation();

    void setLocation(Node *location);
};


#endif //ADPROG1_1_DRIVER_H
