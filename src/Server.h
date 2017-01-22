
#ifndef ADPROG1_1_MAINFLOW_H
#define ADPROG1_1_MAINFLOW_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <list>
#include <iostream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <pthread.h>
#include "Map.h"
#include "BreadthFirstSearch.h"
#include "TaxiStation.h"
#include "Tcp.h"

_INITIALIZE_EASYLOGGINGPP

class Server {
private:
    int task;
    //int clock;
    int port;
    Tcp tcp;
    bool isFirst9;
    //const int server_port = 5555;
    Map* map;
    TaxiStation* taxiStation;
    pthread_mutex_t task_locker;
    pthread_mutex_t thread_locker;
    pthread_mutex_t driver_locker;
    pthread_mutex_t numOfThreads_locker;
    struct ClientInfo {
        Server* server;
        stack <int>* task = new stack<int>;
    };
    list<ClientInfo*>* tasks;

    /**
     * receives a driver and sends a taxi.
     * @param info is the info i need for the thread.
     */
    void receivesDriverAndSendTaxi(int*);
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
    void startDriving(int client);
public:
    TaxiStation *getTaxiStation() const;

    Tcp* getTcp();
    /**
     * constructor.
     * @param columns of the graph.
     * @param rows of the graph.
     */
    Server(int columns, int rows, int portNumber);

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
    static void* createThreadsForDrivers(void* inf);

    int getTask();
};



#endif //ADPROG1_1_MAINFLOW_H
