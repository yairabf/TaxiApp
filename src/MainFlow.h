
#ifndef ADPROG1_1_MAINFLOW_H
#define ADPROG1_1_MAINFLOW_H

#include <iostream>
#include "gtest/gtest.h"
#include "Map.h"
#include "BreadthFirstSearch.h"
#include "TaxiStation.h"
/**
 * this class controls the program flow.
 */
class MainFlow {
private:
    Map* map;
    TaxiStation* taxiStation;

    /**
     * creates a driver.
     */
    void createDriver();

    /**
     *creates a trip info.
     */
    void createTripInfo();

    /**
     *creates a taxi.
     */
    void createVehicle();

    /**
     *requests the location of a driver.
     */
    void requestDriverLocation();

    /**
     *all drivers drive to their destination.
     */
    void startDriving();
public:
    /**
     * constructor.
     * @param columns of the graph.
     * @param rows of the graph.
     */
    MainFlow(const int columns, const int rows);

    /**
     * destructor.
     */
    virtual ~MainFlow();
    /**
     * runs the program.
     */
    void run();

};


#endif //ADPROG1_1_MAINFLOW_H
