
#include <iostream>
#include "Driver.h"
#include "NodeBlock.h"


Driver::Driver(int id, int age,char status1, int yearsExp1, int vehicle_id): id(id), age(age),
                                                                             vehicle_id(vehicle_id)
{
    yearsExp = yearsExp1;
    status = status1;
    taxi = NULL;
    location = NULL;
    tripInfo = NULL;
    occupied = false;

}

int Driver::getId() {
    return id;
}

bool Driver::isOccupied()  {
    return occupied;
}

void Driver::setOccupied(bool occupied) {
    Driver::occupied = occupied;
}


Taxi* Driver::getTaxi() {
    return taxi;
}

float Driver::getAvgSatisfaction()  {
    return avgSatisfaction;
}

void Driver::setAvgSatisfaction(float avgSatisfaction) {
    Driver::avgSatisfaction = avgSatisfaction;
}

Node* Driver::getLocation()  {
    return location;
}


void Driver::setLocation(Node *location) {
    Driver::location = location;
}

TripInfo *Driver::getTripInfo() const {
    return tripInfo;
}

void Driver::assignTaxi(Taxi *taxi) {
    //delete(taxi);
    Driver::taxi = taxi;
}

void Driver::assignTripInfo(TripInfo* tripInfo1) {
    tripInfo = tripInfo1;
    setOccupied(true);
}

void Driver::addPassenger(Passenger* passenger) {
    passengers.push_back(passenger);
}

void Driver::drive() {
    //checking if the driver has been assigned to a route
    if(tripInfo != NULL) {
        stack<Node*> *route = tripInfo->getRoute();
        if(taxi->getSpeed() == 2 && route->size() > 1) {
            route->pop();
        }
        setLocation(route->top());
        //cout << route->top()->printValue() << endl;
        route->pop();
    }
    //getSatisfactionFromPassengers();
    setOccupied(false);
}

double Driver::calculatePrice(int km) {
    double price = tripInfo->getTarrif() * km;
    return price;
}

bool Driver::passengerIsExist(Passenger *passenger) {
    if(passengers.size() > 0) {
        for (std::list<Passenger *>::iterator it = passengers.begin(); it != passengers.end(); it++) {
            if (it.operator*()->getSource() == passenger->getSource() &&
                it.operator*()->getDestination() == passenger->getDestination()) {
                return true;
            }
        }
    }
    return false;
}

int Driver::getVehicle_id() const {
    return vehicle_id;
}

Driver::~Driver() {
    //delete(tripInfo);
    //delete(taxi);
    //delete(location);
}

void Driver::getSatisfactionFromPassengers() {
    /*int sum = 0;
    std::list<Passenger*>::iterator passengerIterator;
    for(passengerIterator = passengers.begin(); passengerIterator != passengers.end();
        ++passengerIterator) {
        Passenger* passenger = *passengerIterator;
        sum += passenger->randomScore();
    }
    avgSatisfaction = sum / passengers.size();*/
}

using namespace std;
using namespace boost::archive;
template<class Archive>
void Driver::serialize(Archive & ar, const unsigned int version) {
    ar & id;
    ar & age;
    ar & yearsExp;
    ar & vehicle_id;
    ar & occupied;
    ar & status;
    ar & taxi;
    ar & avgSatisfaction;
    ar & location;//check if need to serialize node
    ar & tripInfo;
    ar & passengers;


}
/*
 * int id;
    int age;
    int yearsExp;
    int vehicle_id;
    bool occupied;
    char status;
    Taxi* taxi;
    float avgSatisfaction;
    Node* location;
    TripInfo* tripInfo;
    list<Passenger*> passengers;
 */