
#ifndef ADPROG1_1_TAXISTATION_H
#define ADPROG1_1_TAXISTATION_H

#include <cstdlib>
#include <list>
#include "Driver.h"
#include "TripInfo.h"
#include "Map.h"
#include "BreadthFirstSearch.h"
#include "Passenger.h"

using namespace std;

class TaxiStation {
private:
    list<Driver* > drivers;
    list<Taxi* > taxis;
    list<TripInfo* > trips;
    Map* map;
    BreadthFirstSearch* bfs;
    void assignDrivers();
    void sendTaxi(Point);
    Driver* calculateClosestDriver(Point destination);
public:
    TaxiStation(Map *map);

    virtual ~TaxiStation();

    void answerCall(Point destination, Passenger passenger);

    void addDriver(Driver* driver);

    void addTaxi(Taxi* taxi);

    void removeDriver(Driver* driver);

    void removeTaxi(Taxi* taxi);

    list<Driver*>* getDrivers();

    bool doesDriverExist(Driver *driver1);

    bool doesTaxiExist(Taxi *taxi1);
};


#endif //ADPROG1_1_TAXISTATION_H
