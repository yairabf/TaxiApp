
#ifndef ADPROG1_1_MAINFLOW_H
#define ADPROG1_1_MAINFLOW_H

#include <iostream>
#include "Map.h"
#include "BreadthFirstSearch.h"
#include "TaxiStation.h"
#include "Udp.h"
#include "Tcp.h"
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <pthread.h>

class Server {
private:
    //const int server_port = 5555;
    Map* map;
    TaxiStation* taxiStation;
public:
    TaxiStation *getTaxiStation() const;

    const Tcp &getTcp() const;

private:
    int clock;
    Tcp tcp;
    bool isFirst9;

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
    Server(const int columns, const int rows, int portNumber);

    /**
     * destructor.
     */
    virtual ~Server();
    /**
     * rinf the program.
     */
    void run();

    /**
     * creates threads, one for each driver.
     * @param server we are sending the function to have all the members.
     * @return void
     */
    static void* createThreadsForDrivers(void* s);
};


#endif //ADPROG1_1_MAINFLOW_H
