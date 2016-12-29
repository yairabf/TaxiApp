
#include "Taxi.h"
#include <stdexcept>

using namespace std;
using namespace boost::archive;

Taxi::Taxi(int id, char CarManufacturer, char color, int speed) : id(id), carManufacturer(CarManufacturer),
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
    return carManufacturer;
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

template<class Archive>
void Taxi::serialize(Archive & ar, const unsigned int version) {
    ar & id;
    ar & numOfKmPassed;
    ar & carManufacturer;
    ar & color;
    ar & speed;
    ar & tripInfo;
}