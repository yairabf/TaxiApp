
#include <iostream>
#include "Driver.h"
#include "../easylogging++.h"


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


void Driver::setLocation(Node* location) {
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
    LOG(INFO) << "Driver number" << id << " drive";
    //checking if the driver has been assigned to a route
    if((tripInfo != NULL) && (!tripInfo->isDone())) {
        stack<Node*> *route = tripInfo->getRoute();
        route->pop();
        if(taxi->getSpeed() == 2 && route->size() > 1) {
            route->pop();
        }
        //i want to pop the first node that the driver is allready in
        //if(strcmp(location->printValue().data(), route->top()->printValue().data()) == 0)
            //route->pop();
        setLocation(route->top());
    }
    if(tripInfo->getRoute()->size()==1){
        tripInfo->setDone(true);
        setOccupied(false);
    }
    //getSatisfactionFromPassengers();

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
    //if(location != NULL)
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

Driver::Driver() {}


