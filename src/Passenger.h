
#ifndef ADPROG1_1_PASSENGER_H
#define ADPROG1_1_PASSENGER_H


#include "Point.h"
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
#include <boost/serialization/list.hpp>

using namespace std;
using namespace boost::archive;
/**
 * class that represent a passenger in the world. each passenger has a source point which represent
 * the current location of the passenger' and has a destination point that represent the
 * point he wants to go.
 */
class Passenger {
private:
    Point* source;
    Point* destination;

    /**
     * serialization of the class
     * @param ar is the serializing object.
     * @param version is the version of serializing object.
     */
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & source;
        ar & destination;
    }

public:
    Passenger();

    ~Passenger();

    /**
     * getter for the source point
     * @return the current location of the passenger.
     */
    const Point* getSource() const;

    /**
     * getter.
     * @return the destination of the passenger.
     */
    const Point* getDestination() const;

    /**
     * constructor.
     * @param source is where the passenger starts.
     * @param destination where the passenger wants to drive to.
     */
    Passenger(Point* source, Point* destination);

    /**
     * provides a random score for the satisfaction of the passenger between 1 to 5.
     * @return the satisfaction level.
     */
    int randomScore();
};

#endif //ADPROG1_1_PASSENGER_H


