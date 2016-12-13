
#ifndef ADPROG1_1_TRIPINFO_H
#define ADPROG1_1_TRIPINFO_H


#include <stack>
#include "Point.h"
#include "Node.h"

class TripInfo {
private:
    int id;
    int metersPassed;
    Point start;
    Point end;
    int numberOfPassengers;
    double tariff;
    std::stack <Node*> *route;
public:

	/**
     * constructor.
     * @param s dtart point.
     * @param e end point.
     * @return a new trip info.
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
     * getter.
     * @return the starting point.
     */
    const Point &getStart() const;

    /**
     * getter.
     * @return the end point.
     */
    const Point &getEnd() const;

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
     * getter.
     * @return the route for the trip as a stack.
     */
    std::stack<Node *>* getRoute() const;
};


#endif //ADPROG1_1_TRIPINFO_H
