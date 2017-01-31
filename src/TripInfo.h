
#ifndef ADPROG1_1_TRIPINFO_H
#define ADPROG1_1_TRIPINFO_H


#include <deque>
#include "Point.h"
#include "Node.h"
#include <boost/serialization/map.hpp>
#include <boost/serialization/deque.hpp>
#include <stack>

using namespace boost::archive;

class TripInfo {
private:
    int id;
    int start_time;
    bool assigned;
    bool done;
    int metersPassed;
    Point* start;
    Point* end;
    int numberOfPassengers;
    double tariff;
    std::stack <Node*>* route;

    /**
     * serialization of the class
     * @param ar is the serializing object.
     * @param version is the version of serializing object.
     */
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & start_time;
        ar & assigned;
        ar & done;
        ar & metersPassed;
        ar & start;
        ar & end;
        ar & numberOfPassengers;
        ar & tariff;
       // ar & route;
    }

public:
    /**
     * constructor.
     * @param id  of the trip.
     * @param x_start where the trip starts on x axis.
     * @param y_start where the trip starts on the y axis.
     * @param x_end where the trip ends on x axis.
     * @param y_end where the trip ends on y axis.
     * @param num_of_passenger number of passengers on the trip.
     * @param tariff how much the trip costs.
     */
    TripInfo(int id, int x_start, int y_start, int x_end, int y_end, int num_of_passenger,
                       double tariff, int start_time);
    /**
     * getter.
     * @return the id of the trip info.
     */
    int getId() const;

    int getStart_time() const;

    TripInfo();

    /**
     * getter.
     * @return amount of meters the trip has passed so far..
     */
    int getMetersPassed() const;

    /**
     * destructor.
     */
    virtual ~TripInfo();

    /**
     * has the trip finished
     * @return true if it has finished, otherwise, false.
     */
    bool isDone() const;
    /**
     * sets if the trip has ended.
     * @param done
     */
    void setDone(bool done);

    /**
     * getter.
     * @return the starting point.
     */
    Point* getStart();

    /**
     * getter.
     * @return tTripInfo.h:6he end point.
     */
    Point* getEnd();

    /**
     * getter.
     * @return the amount of passengers.
     */
    int getNumberOfPassengers() const;

    /**
     * getter.
     * @return the tariff for the trip.
     */
    double getTarrif() const;

    bool isAssigned() const;

    /**
     * sets a route to the trip info.
     * @param route is the new route.
     */
    void setRoute(std::stack<Node*>* route);
    /**
     * getter.
     * @return the route for the trip as a stack.
     */
    std::stack<Node *>* getRoute() const;

    void setAssigned(bool assigned);

};


#endif //ADPROG1_1_TRIPINFO_H
