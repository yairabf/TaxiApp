
#include "TaxiStation.h"
#include "InfoForTripThread.h"

TaxiStation::TaxiStation(Map *map) : map(map), bfs(BreadthFirstSearch(map)),threadPool(new ThreadPool(5)) {
    clock = 0;
    pthread_mutex_init(&this->map_locker, NULL);
    pthread_mutex_init(&this->tripAssign_locker, NULL);
    pthread_mutex_init(&this->addingTrip_locker, NULL);
}

TaxiStation::~TaxiStation() {
    std::list<Taxi*>::iterator iteratorTaxis;
    std::list<Driver*>::iterator iteratorDrivers;
    std::list<TripInfo*>::iterator iteratorTrips;
    threadPool->terminate();
    delete (threadPool);
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

void TaxiStation::addTrip(TripInfo* tripInfo) {
    //pthread_t routeThread;
    InfoForTripThread* info = new InfoForTripThread(this, tripInfo);
    //creating the best route for the trip using bfs
    Job* bsfCal = new Job(creatingRouteByThread, (void*)info);
    threadPool->addJob(bsfCal);
}

void* TaxiStation::creatingRouteByThread(void* info) {
    LOG(INFO) << "Hello From from bfs";
    pthread_mutex_t locker;
    pthread_mutex_init(&locker, NULL);
    pthread_mutex_lock(&locker);
    InfoForTripThread* inf = (InfoForTripThread*)info;
    TaxiStation* taxiStation = inf->getTaxiStation();
    TripInfo* tripInfo = inf->getTripInfo();
    Node* startLocation = taxiStation->map->getBlock(*tripInfo->getStart());
    Node* endLocation = taxiStation->map->getBlock(*tripInfo->getEnd());
    //pthread_mutex_lock(&taxiStation->map_locker);
    taxiStation->map->resetVisited();
    std::stack<Node*> tempRoute = taxiStation->bfs.breadthFirstSearch(startLocation, endLocation);
    std::stack<Node*>* route = new stack<Node*>(tempRoute);
    //if the route is empty
    if(route->size() > 1) {
        inf->getTripInfo()->setRoute(route);
        inf->getTaxiStation()->trips.push_back(inf->getTripInfo());
        LOG(INFO) << " a trip has been added to taxi station";
    }
    delete(inf);
    pthread_mutex_unlock(&locker);
    pthread_mutex_destroy(&locker);
    //pthread_exit(NULL);
}

list<Driver *> *TaxiStation::getDrivers() {
    return &drivers;
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

Driver* TaxiStation::getDriverById(int id) {
    std::list<Driver*>::iterator iteratorDrivers;
    for(iteratorDrivers = drivers.begin(); iteratorDrivers != drivers.end(); ++iteratorDrivers) {
        Driver* driver = *iteratorDrivers;
        if(driver->getId() == id)
            return driver;
    }
}

void TaxiStation::assignTripToDriver(Driver* driver) {
    std::list<TripInfo*>::iterator tripInfoIterator = trips.begin();
    if(!(driver->isOccupied())) {
        pthread_mutex_lock(&this->tripAssign_locker);
        while (tripInfoIterator != trips.end()) {
            if((*tripInfoIterator)->getStart_time() == clock && !(*tripInfoIterator)->isAssigned()) {
                //assigns the correct driver to the trip
                if (driver->getLocation()->printValue() == (*tripInfoIterator)->getStart()->toString() &&
                    !(*tripInfoIterator)->isDone()) {
                    driver->assignTripInfo((*tripInfoIterator));
                    (*tripInfoIterator)->setAssigned(true);
                    LOG(INFO) << "driver with id: " << driver->getId() << " received trip id: "
                              << (*tripInfoIterator)->getId();
                    pthread_mutex_unlock(&this->tripAssign_locker);
                    break;
                }
            }
            tripInfoIterator++;
        }
        pthread_mutex_unlock(&this->tripAssign_locker);
    }
}

void TaxiStation::driveOneDriver(Driver* driver) {
    if(driver->getTripInfo() != NULL) {
        driver->drive();
    }
}

void TaxiStation::advanceClock() {
    clock++;
}

int TaxiStation::getClock(){
    return clock;
}

int TaxiStation::getColumns() {
    return map->getColumns();
}

int TaxiStation::getRows() {
    return map->getRows();
}

ThreadPool* TaxiStation::getThreadPool() const {
    return threadPool;
}

list<TripInfo *>* TaxiStation::getTrips()  {
    return &trips;
}


