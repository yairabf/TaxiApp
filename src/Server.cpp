#include "Server.h"
#include "ClientDriver.h"

Server::Server(const int columns, const int rows) {
    map = new Map(columns, rows);
    taxiStation = new TaxiStation(map);
    clock = 0;
    udp = Udp(1, server_port);
    udp.initialize();
}

void Server::run() {
    int numberOfObstacles, x, y;
    char temp;
    cin >> numberOfObstacles;
    if(numberOfObstacles > 0 ) {
        //waits for obstacles input
        //need to add a test that checks if the obstacles have been inserted correctly.
        for(int i = 1; i <= numberOfObstacles; i++) {
            cin >> x >> temp >> y;
            taxiStation->setObstacle(x, y);
        }
    }
    int task;
    do {
        cin >> task;
        switch (task) {
            case 1:
                if(udp.Socket().)
                createDriver();
                break;
            case 2:
                createTripInfo();
                break;
            case 3:
                createVehicle();
                break;
            case 4:
                requestDriverLocation();
                break;
            case 6:
                startDriving();
                map->resetVisited();
                break;
            default:
                break;
        }
    }  while (task != 7);
    exit(0);
}

void Server::createDriver() {
    /*int id, age, experience, vehicle_id;
    char status , temp;
    //receiving driver details
    cin >> id >> temp >> age >> temp >> status >> temp >> experience >> temp >> vehicle_id;
    Driver* driver = new Driver(id,age,status,experience,vehicle_id);
    taxiStation->addDriver(driver);*/

    //need to create a port and send it to the ClientDriver
    ClientDriver clientDriver(;//need to add a port number.
}

Server::~Server() {
    delete (taxiStation);
    delete (map);
}

void Server::createTripInfo() {
    int id, x_start, y_start, x_end, y_end, num_of_passenger;
    double tariff;
    char temp;
    //receiving trip details
    cin >> id >> temp >> x_start >> temp >> y_start >> temp >> x_end >> temp >> y_end >> temp
        >> num_of_passenger >> temp >> tariff;
    TripInfo *tripInfo = new TripInfo(id, x_start, y_start, x_end, y_end, num_of_passenger, tariff);
    taxiStation->addTrip(tripInfo);
}

void Server::createVehicle() {
    int id, taxi_type;
    char manufacturer, color, temp;
    //receiving trip details
    cin >> id >> temp >> taxi_type >> temp >> manufacturer >> temp >> color;
    Taxi *taxi = new Taxi(id, manufacturer, color, taxi_type);
    taxiStation->addTaxi(taxi);
}

void Server::requestDriverLocation() {
    int id;
    cin >> id;
    list<Driver*>::iterator it = taxiStation->getDrivers()->begin();
    while(it != taxiStation->getDrivers()->end()) {
        if(it.operator*()->getId() == id) {
            cout << it.operator*()->getLocation()->printValue() << endl;
            break;
        }
        it++;
    }
}

void Server::startDriving() {
    taxiStation->driveAll();
}

/**
 * The main method that runs the program, the method receives form the user the size of the grid
 * and the location of the start point and the goal and the method prints the the fastest route.
 */
int main(int argc, char** argv) {
    int columns, rows;
    cin >> columns;
    cin >> rows;
    Server server = Server(columns, rows);
    server.run();
    return 1;
}


