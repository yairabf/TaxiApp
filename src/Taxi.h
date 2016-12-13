
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
    char CarManufacturer;
    char color;
    int speed;
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
    Taxi(int id, char CarManufacturer, char color, int speed);

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
    const char &getCarManufacturer() const;

    /**
     * getter.
     * @return the color of the taxi.
     */
    const char &getColor() const;

    void setTripInfo(TripInfo *tripInfo);

    /**
     * getter.
     * @return the speed of the taxi.
     */
    int getSpeed() const;

    /**
     * calculates the price for the drive.
     * @param km how many km the journet is.
     * @return the price.
     */
    double calculatePrice(int km) const;

    /**
     * getter.
     * @return the trip info.
     */
    TripInfo *getTripInfo() const;
};


#endif //ADPROG1_1_TAXI_H