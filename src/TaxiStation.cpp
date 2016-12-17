
#include "TaxiStation.h"

Driver* TaxiStation::calculateClosestDriver(Point destination) {
    return NULL;
}

void TaxiStation::sendTaxi(Point) {

}

void TaxiStation::assignDrivers() {
    std::list<Driver*>::iterator iteratorDrivers;
    std::list<TripInfo*>::iterator tripInfoIterator = trips.begin();
    while (tripInfoIterator != trips.end()) {
        //assigns the correct driver to the trip
        for (iteratorDrivers = drivers.begin(); iteratorDrivers != drivers.end();
             ++iteratorDrivers) {
            if ((*iteratorDrivers)->getLocation()->printValue() ==
                        (*tripInfoIterator)->getStart()->toString() &&
                    !(*tripInfoIterator)->isDone() && !(*iteratorDrivers)->isOccupied()) {
                (*iteratorDrivers)->assignTripInfo((*tripInfoIterator));
                break;
            }
        }
        tripInfoIterator++;
    }
}

void TaxiStation::answerCall(Point destination, Passenger *passenger) {

}

TaxiStation::TaxiStation(Map *map) : map(map), bfs(BreadthFirstSearch(map)) {
}

void TaxiStation::addDriver(Driver *driver) {
    NodeBlock* startingLocation = map->getBlock(Point(0,0));
    driver->setLocation(startingLocation);
    std::list<Taxi*>::iterator taxiIterator;
    //assigns the correct taxi to the driver.
    for(taxiIterator = taxis.begin(); taxiIterator != taxis.end(); ++taxiIterator) {
        Taxi* currentTaxi = *taxiIterator;
        //if their ids are matching ,assign
        if(driver->getVehicle_id() == currentTaxi->getId()) {
            driver->assignTaxi(currentTaxi);
            break;
        }
    }
    drivers.push_back(driver);
}

void TaxiStation::addTaxi(Taxi *taxi) {
    taxis.push_back(taxi);
}

void TaxiStation::removeDriver(Driver *driver) {
    delete(driver);
    drivers.remove(driver);
}

void TaxiStation::removeTaxi(Taxi *taxi) {
    delete(taxi);
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
    std::list<Taxi*>::iterator iteratorTaxis;
    std::list<Driver*>::iterator iteratorDrivers;
    std::list<TripInfo*>::iterator iteratorTrips;
    for (iteratorTaxis = taxis.begin(); iteratorTaxis != taxis.end(); ++iteratorTaxis) {
        Taxi *tempTaxi = *iteratorTaxis;
        delete(tempTaxi);
    }
    for (iteratorDrivers = drivers.begin(); iteratorDrivers != drivers.end(); ++iteratorDrivers) {
        Driver *tempDriver = *iteratorDrivers;
        //if (tempDriver->getTripInfo() != NULL)
         //   delete (tempDriver->getTripInfo());
        delete (tempDriver);
    }
    for (iteratorTrips = trips.begin(); iteratorTrips != trips.end(); ++iteratorTrips) {
        TripInfo *tempTripInfo = *iteratorTrips;
        delete(tempTripInfo->getRoute());
        delete(tempTripInfo);
    }
}

void TaxiStation::addTrip(TripInfo* tripInfo) {
    Node* startLocation = map->getBlock(*tripInfo->getStart());
    Node* endLocation = map->getBlock(*tripInfo->getEnd());
    //creating the best route for the trip using bfs
    map->resetVisited();
    std::stack<Node*> tempRoute = bfs.breadthFirstSearch(startLocation, endLocation);
    std::stack<Node*> *route = new stack<Node*>(tempRoute);
    tripInfo->setRoute(route);
    trips.push_back(tripInfo);
}

void TaxiStation::driveAll() {
    assignDrivers();
    std::list<Driver*>::iterator iteratorDrivers;
    for(iteratorDrivers = drivers.begin(); iteratorDrivers != drivers.end(); ++iteratorDrivers) {
        Driver* driver = *iteratorDrivers;
        driver->drive();
        driver->getTripInfo()->setDone(true);
    }
}

void TaxiStation::setObstacle(int x, int y) {
    map->setObstacle(Point(x, y));
}
