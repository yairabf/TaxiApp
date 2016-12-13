
#include "Driver.h"
#include "NodeBlock.h"

Driver::Driver(int id, int age,char status, int yearsExp, int vehicle_id): id(id), age(age),
                                                                             status(status),
                                                                             yearsExp(yearsExp),
                                                                             vehicle_id(vehicle_id)
                                                                       {
    taxi = NULL;
    location = NULL;
    tripInfo = NULL;
}

int Driver::getId() {
    return id;
}

int Driver::getYearsExp()  {
    return yearsExp;
}

void Driver::setYearsExp(int yearsExp) {
    Driver::yearsExp = yearsExp;
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

Node *Driver::getLocation()  {
    return location;
}

void Driver::setLocation(Node *location) {
    Driver::location = location;
}

TripInfo *Driver::getTripInfo() const {
    return tripInfo;
}

void Driver::assignTaxi(Taxi *taxi) {
    Driver::taxi = taxi;
}

void Driver::addPassenger(Passenger* passenger) {
    passengers.push_back(passenger);
}

void Driver::drive(stack<Node *>* route) {
    while(route->size() > 0){
        setLocation(route->top());
        route->pop();
    }
}

double Driver::calculatePrice(int km) {
    double price = taxi->getTripInfo()->getTarrif() * km;
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
