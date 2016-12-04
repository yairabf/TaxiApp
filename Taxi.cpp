
#include "Taxi.h"
#include <stdexcept>

Taxi::Taxi(int id, int km, string carMan, string color, int speed, float tariff) {
    this->id = id;
    this->numOfKmPassed = km;
    this->CarManufacturer = carMan;
    this->color = color;
    this->speed = speed;
    this->tariff = tariff;
}

int Taxi::getId() const {
    return id;
}

int Taxi::getNumOfKmPassed() const {
    return numOfKmPassed;
}

const string &Taxi::getCarManufacturer() const {
    return CarManufacturer;
}

const string &Taxi::getColor() const {
    return color;
}

int Taxi::getSpeed() const {
    return speed;
}

float Taxi::getTariff() const {
    return tariff;
}

float Taxi::calculatePrice(int km) const {
    if(km < 0) {
        throw std::invalid_argument("Received negative value.");
    }
    return km * tariff;
}

TripInfo *Taxi::getTripInfo() const {
    return tripInfo;
}
