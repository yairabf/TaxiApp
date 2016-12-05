
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
    /**
     * constructor.
     * @param id taxis id.
     * @param km is how many km the taxi passed.
     * @param carMan is the car manufacturer.
     * @param color is the color of the taxi.
     * @param speed is the speed of the taxi.
     * @param tariff is the amount to be paid for the taxi.
     * @return a new taxi.
     */
    Taxi(int id, int km, string carMan, string color, int speed, float tariff);
    /**
     * getter.
     * @return the id of the taxi.
     */
    int getId() const;
    /**
     * getter.
     * @return the numOfKmPassed.
     */
    int getNumOfKmPassed() const;
    /**
     * getter.
     * @return the car manufacturer.
     */
    const string &getCarManufacturer() const;
    /**
     * getter.
     * @return the color of the taxi.
     */
    const string &getColor() const;
    /**
     * getter.
     * @return the speed of the taxi.
     */
    int getSpeed() const;
    /**
     * getter.
     * @return the tariff of the taxi.
     */
    float getTariff() const;
    /**
     * calculates the price for the drive.
     * @param km how many km the journet is.
     * @return the price.
     */
    float calculatePrice(int km) const;
    /**
     * getter.
     * @return the trip info.
     */
    TripInfo *getTripInfo() const;
};


#endif //ADPROG1_1_TAXI_H