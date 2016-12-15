
#include "Taxi.h"
#include <stdexcept>

Taxi::Taxi(int id, char CarManufacturer, char color, int speed) : id(id), CarManufacturer(CarManufacturer),
                                                                  color(color), speed(speed) {
    tripInfo = NULL;
    numOfKmPassed = 0;
}
int Taxi::getId() const {
    return id;
}

int Taxi::getNumOfKmPassed() const {
    return numOfKmPassed;
}

const char &Taxi::getCarManufacturer() const {
    return CarManufacturer;
}

const char &Taxi::getColor() const {
    return color;
}

int Taxi::getSpeed() const {
    return speed;
}

double Taxi::calculatePrice(int km) const {
    if(km < 0) {
        throw std::invalid_argument("Received negative value.");
    }
    return km * tripInfo->getTarrif();
}

TripInfo *Taxi::getTripInfo() const {
    return tripInfo;
}

void Taxi::setTripInfo(TripInfo *tripInfo) {
    Taxi::tripInfo = tripInfo;
}


