
#ifndef ADPROG1_1_TRIPINFO_H
#define ADPROG1_1_TRIPINFO_H


#include <stack>
#include "Point.h"
#include "Node.h"

class TripInfo {
private:
    int id;
    bool done;
    int metersPassed;
    Point start;
    Point end;
    int numberOfPassengers;
    double tariff;
    std::stack <Node*> *route;

    friend class boost::serialization::access;
    /**
     * serialization of the class
     * @param ar is the serializing object.
     * @param version is the version of serializing object.
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);

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
                       double tariff);
    /**
     * getter.
     * @return the id of the trip info.
     */
    int getId() const;

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
     * @return the end point.
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

    /**
     * sets a route to the trip info.
     * @param route is the new route.
     */
    void setRoute(std::stack<Node*> *route);
    /**
     * getter.
     * @return the route for the trip as a stack.
     */
    std::stack<Node *>* getRoute() const;

};


#endif //ADPROG1_1_TRIPINFO_H
