
#ifndef ADPROG1_1_MAINFLOW_H
#define ADPROG1_1_MAINFLOW_H

#include <iostream>
#include "Map.h"
#include "BreadthFirstSearch.h"
#include "TaxiStation.h"
#include "Udp.h"

class Server {
private:
    const int server_port = 4;
    Map* map;
    TaxiStation* taxiStation;
    int clock;
    Udp udp = NULL;//check if this is ok

    /**
     * creeates a driver.
     */
    void createDriver();

    /**
     * creates a trip info.
     */
    void createTripInfo();

    /**
     * creates a taxi.
     */
    void createVehicle();

    /**
     * requests a drivers location according to an id.
     */
    void requestDriverLocation();

    /**
     * all drivers drive to their destinations.
     */
    void startDriving();
public:
    /**
     * constructor.
     * @param columns of the graph.
     * @param rows of the graph.
     */
    Server(const int columns, const int rows);

    /**
     * destructor.
     */
    virtual ~Server();
    /**
     * rinf the program.
     */
    void run();

};


#endif //ADPROG1_1_MAINFLOW_H
