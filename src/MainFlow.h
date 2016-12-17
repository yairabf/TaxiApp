
#ifndef ADPROG1_1_MAINFLOW_H
#define ADPROG1_1_MAINFLOW_H

#include <iostream>
#include "gtest/gtest.h"
#include "Map.h"
#include "BreadthFirstSearch.h"
#include "TaxiStation.h"

class MainFlow {
private:
    Map* map;
    TaxiStation* taxiStation;

    /**
     *
     */
    void createDriver();

    /**
     *
     */
    void createTripInfo();

    /**
     *
     */
    void createVehicle();

    /**
     *
     */
    void requestDriverLocation();

    /**
     *
     */
    void startDriving();
public:
    /**
     *
     * @param columns
     * @param rows
     */
    MainFlow(const int columns, const int rows);

    /**
     *
     */
    virtual ~MainFlow();
    /**
     *
     */
    void run();

};


#endif //ADPROG1_1_MAINFLOW_H
