
#ifndef ADPROG1_1_DRIVER_H
#define ADPROG1_1_DRIVER_H

#include <string>
#include <list>
#include "Node.h"
#include "Taxi.h"
#include "Passenger.h"

using namespace std;

/**
 * Class that represent a taxi driver. the driver can receives a tripInfo
 */
class Driver {
private:
    int id;
    int age;
    int yearsExp;
    bool occupied;
    string status;
    Taxi* taxi;
    float avgSatisfaction = 0;
    Node* location;
    TripInfo* tripInfo;
    list<Passenger*> passengers;

public:
    Driver(int id, int age, int yearsExp, string status);

    int getId();

    int getYearsExp();

    void setYearsExp(int yearsExp);

    bool isOccupied();

    void setOccupied(bool occupied);

    TripInfo *getTripInfo() const;

    Taxi *getTaxi();

    void assignTaxi(Taxi *taxi);

    float getAvgSatisfaction();

    void setAvgSatisfaction(float avgSatisfaction);

    Node *getLocation();

    void setLocation(Node *location);

    void addPassenger(Passenger* passenger);

    bool passengerIsExist(Passenger* passenger);

    void drive(stack<Node*>* route);

    float calculatePrice(int km);

};


#endif //ADPROG1_1_DRIVER_H
