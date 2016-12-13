
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
    float avgSatisfaction;
    Node* location;
    TripInfo* tripInfo;
    list<Passenger*> passengers;

public:
	/**
	* constructor
	*/
    Driver(int id, int age, int yearsExp, string status);

     /**
     * getter.
     * @return the id.
     */
    int getId();

/**
     * getter.
     * @return yearsExp.
     */
    int getYearsExp();

/**
     * setter.
     * @param yearsExp is the years of experience.
     */
    void setYearsExp(int yearsExp);

/**
     * checks if the driver is occupied.
     * @return true id the driver is occupied.
     */
    bool isOccupied();

/**
     * setter.
     * @param occupied the state of the driver.
     */
    void setOccupied(bool occupied);

/**
     * getter.
     * @return the trip info.
     */
    TripInfo *getTripInfo() const;

/**
     * getter.
     * @return the taxi.
     */
    Taxi *getTaxi();

/**
     * assigns a taxi to the driver.
     * @param taxi is the taxi for the driver.
     */
    void assignTaxi(Taxi *taxi);

 /**
     * getter.
     * @return the average satisfaction of the driver.
     */
    float getAvgSatisfaction();

 /**
     * setter.
     * @param avgSatisfaction the satisfaction of the driver.
     */
    void setAvgSatisfaction(float avgSatisfaction);

/**
     * getter.
     * @return the location of the driver.
     */
    Node *getLocation();

/**
     * setter.
     * @param location the new location of the driver.
     */
    void setLocation(Node *location);

/**
     * adds a passenger to the passengers list.
     * @param passenger is the passenger to be added.
     */
    void addPassenger(Passenger* passenger);

/**
     * checks if the passenger is in the list.
     * @param passenger is the passenger to be added.
     * @return true if the passenger is on the list.
     */
    bool passengerIsExist(Passenger* passenger);

/**
     * makes the driver drive.
     * @param route is the route he should drive by.
     */
    void drive(stack<Node*>* route);

 /**
     * calculates the price to pay.
     * @param km is how many km the drive is.
     * @return the price.
     */
    float calculatePrice(int km);

};


#endif //ADPROG1_1_DRIVER_H
