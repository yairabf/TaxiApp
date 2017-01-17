
#ifndef ADPROG1_1_TAXI_H
#define ADPROG1_1_TAXI_H

#include <cstdlib>
#include <string>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "TripInfo.h"

using namespace std;
using namespace boost::archive;
class Taxi {
private:
    int id;
    int numOfKmPassed;
    char carManufacturer;
    char color;
    int speed;

public:
    Taxi();

private:
    /**
     * serialization of the class
     * @param ar is the serializing object.
     * @param version is the version of serializing object.
     */
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & id;
        ar & numOfKmPassed;
        ar & carManufacturer;
        ar & color;
        ar & speed;
    }
public:
	
	/**
     * constructor.
     * @param id taxis id.
     * @param km is how many km the taxi passed.
     * @param carMan is the car manufacturer.
     * @param color is the color of the taxi.
     * @param speed is the speed of the taxi.
     * @param tariff is the amount to be paid for the taxi.
     * @return a new taxi.
     */
    Taxi(int id, char CarManufacturer, char color, int speed);

    /**
     * getter.
     * @return the id of the taxi.
     */
    int getId() const;

    /**
     * getter.
     * @return the numOfKmPassed.
     */
    int getNumOfKmPassed() const;

    /**
     * getter.
     * @return the car manufacturer.
     */
    const char &getCarManufacturer() const;

    /**
     * getter.
     * @return the color of the taxi.
     */
    const char &getColor() const;

    /**
     * getter.
     * @return the speed of the taxi.
     */
    int getSpeed() const;

    /**
     * calculates the price for the drive.
     * @param km how many km the journet is.
     * @return the price.
     */
    double calculatePrice(int km) const;
};


#endif //ADPROG1_1_TAXI_H