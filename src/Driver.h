
#ifndef ADPROG1_1_DRIVER_H
#define ADPROG1_1_DRIVER_H

#include <string>
#include <list>
#include "Node.h"
#include "Taxi.h"
#include "Passenger.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
using namespace boost::archive;

/**
 * Class that represent a taxi driver. the driver can receives a tripInfo
 */
class Driver {
private:
    int id;
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

    /**
     * updates the satisfaction of the passengers.
     */
    void getSatisfactionFromPassengers();

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
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

public:
    /**
    * constructor
    */
    Driver(int id, int age, char status, int yearsExp, int vehicle_id);

    /**
    * getter.
    * @return the id.
    */
    int getId();

    Driver();

    /**
     * getter.
     * @return the taxi id.
     */
    int getVehicle_id() const;


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
    Taxi* getTaxi();

    /**
     * assigns a taxi to the driver.
     * @param taxi is the taxi for the driver.
     */
    void assignTaxi(Taxi *taxi);

    /**
     * assif-gnins a trip info to the driver.
     * @param tripInfo it the trip
     */
    void assignTripInfo(TripInfo* tripInfo1);

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
    void drive();


    /**
        * calculates the price to pay.
        * @param km is how many km the drive is.
        * @return the price.
        */
    double calculatePrice(int km);

    /**
     * destructor.
     */
    ~Driver();


};


#endif //ADPROG1_1_DRIVER_H
