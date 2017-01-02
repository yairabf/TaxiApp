
#include "TaxiStation.h"
#include "Udp.h"

TaxiStation::TaxiStation(Map *map) : map(map), bfs(BreadthFirstSearch(map)) {
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
        delete (tempDriver);
    }
    for (iteratorTrips = trips.begin(); iteratorTrips != trips.end(); ++iteratorTrips) {
        TripInfo *tempTripInfo = *iteratorTrips;
        delete(tempTripInfo);
    }
}

void TaxiStation::addTaxi(Taxi *taxi) {
    taxis.push_back(taxi);
}

void TaxiStation::removeTaxi(Taxi *taxi) {
    taxis.remove(taxi);
    delete(taxi);
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
void TaxiStation::removeDriver(Driver *driver) {
    drivers.remove(driver);
    delete(driver);
}

void TaxiStation::addTrip(TripInfo* tripInfo) {
    Node* startLocation = map->getBlock(*tripInfo->getStart());
    Node* endLocation = map->getBlock(*tripInfo->getEnd());
    //creating the best route for the trip using bfs
    map->resetVisited();
    deque<Node*> tempRoute = bfs.breadthFirstSearch(startLocation, endLocation);
    std::deque<Node*>* route = new deque<Node*>(tempRoute);
    tripInfo->setRoute(route);
    trips.push_back(tripInfo);
}

list<Driver *> *TaxiStation::getDrivers() {
    return &drivers;
}

void TaxiStation::assignDrivers(int time, Udp udp) {
    std::list<Driver*>::iterator iteratorDrivers;
    std::list<TripInfo*>::iterator tripInfoIterator = trips.begin();
    while (tripInfoIterator != trips.end()) {
        if((*tripInfoIterator)->getStart_time() == time && !(*tripInfoIterator)->isAssigned()) {
            //assigns the correct driver to the trip
            for (iteratorDrivers = drivers.begin(); iteratorDrivers != drivers.end();
                 ++iteratorDrivers) {
                if ((*iteratorDrivers)->getLocation()->printValue() == (*tripInfoIterator)->getStart()->toString() &&
                    !(*tripInfoIterator)->isDone() && !(*iteratorDrivers)->isOccupied()) {
                    (*iteratorDrivers)->assignTripInfo((*tripInfoIterator));
                    (*tripInfoIterator)->setAssigned(true);
                    udp.sendData(tripInfoSerialize((*tripInfoIterator)),tripInfoSerialize((*tripInfoIterator)).length());
                    break;
                }

            }
        }
        tripInfoIterator++;
    }
}

void TaxiStation::driveAll(int time) {
    std::list<Driver*>::iterator iteratorDrivers;
    for(iteratorDrivers = drivers.begin(); iteratorDrivers != drivers.end(); ++iteratorDrivers) {
        Driver* driver = *iteratorDrivers;
        if(driver->getTripInfo() != NULL) {
            driver->drive();
        }
    }
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

bool TaxiStation::doesDriverExist(Driver *driver1) {
    if (drivers.size() > 0) {
        for (std::list<Driver *>::iterator it = drivers.begin(); it != drivers.end(); it++) {
            if (it.operator*()->getId() == driver1->getId()) {
                return true;
            }
        }
    }
    return false;
}

void TaxiStation::setObstacle(int x, int y) {
    map->setObstacle(Point(x, y));
}

void TaxiStation::answerCall(Point destination, Passenger *passenger) {

}

Driver* TaxiStation::calculateClosestDriver(Point destination) {
    return NULL;
}

void TaxiStation::sendTaxi(Point) {

}

string TaxiStation::tripInfoSerialize(TripInfo *tripInfo) {
    string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    TripInfo *tripInfo1;
    tripInfo1 = tripInfo;
    oa << tripInfo1;
    s.flush();
    return serial_str;
}