
#ifndef ADPROG1_1_TAXI_H
#define ADPROG1_1_TAXI_H

#include <cstdlib>
#include <string>
#include "TripInfo.h"

using namespace std;
class Taxi {
private:
    int id;
    int numOfKmPassed;
    string CarManufacturer;
    string color;
    int speed;
    float tariff;
    TripInfo* tripInfo;
public:
    Taxi(int id, int km, string carMan, string color, int speed, float tariff);

    int getId() const;

    int getNumOfKmPassed() const;

    const string &getCarManufacturer() const;

    const string &getColor() const;

    int getSpeed() const;

    float getTariff() const;

    float calculatePrice(int km) const;

    TripInfo *getTripInfo() const;
};


#endif //ADPROG1_1_TAXI_H