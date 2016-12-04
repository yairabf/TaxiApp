
#include "Driver.h"
#include "NodeBlock.h"

Driver::Driver(int id, int age, int yearsExp, string status) : id(id), age(age), yearsExp(yearsExp),
                                                                      status(status) {}

int Driver::getId() {
    return id;
}

void Driver::setId(int id) {
    Driver::id = id;
}

int Driver::getAge() {
    return age;
}

void Driver::setAge(int age) {
    Driver::age = age;
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

const string &Driver::getStatus()  {
    return status;
}

void Driver::setStatus(string status) {
    Driver::status = status;
}

Taxi *Driver::getTaxi() {
    return taxi;
}

void Driver::setTaxi(Taxi *taxi) {
    Driver::taxi = taxi;
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

void Driver::setLocation(Point p) {
    this->location = new NodeBlock(p);
}

TripInfo *Driver::getTripInfo() const {
    return tripInfo;
}
