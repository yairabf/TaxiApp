//
// Created by yair on 04/12/16.
//

#include "TaxiStation.h"

Driver* TaxiStation::calculateClosestDriver(Point destination) {
    return nullptr;
}

void TaxiStation::sendTaxi(Point) {

}

void TaxiStation::assignDrivers() {

}

void TaxiStation::answerCall(Point destination, Passenger *passenger) {

}

TaxiStation::TaxiStation(Map *map) : map(map) {
    bfs = new BreadthFirstSearch(map);
    assignDrivers();
}

void TaxiStation::addDriver(Driver *driver) {
    drivers.push_back(driver);
}

void TaxiStation::addTaxi(Taxi *taxi) {
    taxis.push_back(taxi);
}

void TaxiStation::removeDriver(Driver *driver) {
    drivers.remove(driver);
}

void TaxiStation::removeTaxi(Taxi *taxi) {
   taxis.remove(taxi);
}

list<Driver *> *TaxiStation::getDrivers() {
    return &drivers;
}

bool TaxiStation::doesDriverExist(Driver *driver1) {
    if(drivers.size() > 0) {
        for (std::list<Driver *>::iterator it = drivers.begin(); it != drivers.end(); it++) {
            if (it.operator*()->getId() == driver1->getId()) {
                return true;
            }
        }
    }
    return false;
}
bool TaxiStation::doesTaxiExist(Taxi *taxi1) {
    if(taxis.size() > 0) {
        for (std::list<Taxi *>::iterator it = taxis.begin(); it != taxis.end(); it++) {
            if (it.operator*()->getId() == taxi1->getId()) {
                return true;
            }
        }
    }
    return false;
}

TaxiStation::~TaxiStation() {
    delete map;
}
