
#include "Taxi.h"
#include <stdexcept>


Taxi::Taxi(int id, char CarManufacturer, char color, int speed) : id(id), carManufacturer(CarManufacturer),
                                                                  color(color), speed(speed) {
    numOfKmPassed = 0;
}
int Taxi::getId() const {
    return id;
}

int Taxi::getNumOfKmPassed() const {
    return numOfKmPassed;
}

const char &Taxi::getCarManufacturer() const {
    return carManufacturer;
}

const char &Taxi::getColor() const {
    return color;
}

int Taxi::getSpeed() const {
    return speed;
}


Taxi::Taxi() {}

