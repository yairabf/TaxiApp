
#include "MainFlow.h"

MainFlow::MainFlow(const int columns, const int rows) {
    map = new Map(columns, rows);
    taxiStation = new TaxiStation(map);
}

void MainFlow::run() {
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

void MainFlow::createDriver() {
    int id, age, experience, vehicle_id;
    char status , temp;
    //receiving driver details
    cin >> id >> temp >> age >> temp >> status >> temp >> experience >> temp >> vehicle_id;
    Driver* driver = new Driver(id,age,status,experience,vehicle_id);
    taxiStation->addDriver(driver);
}

MainFlow::~MainFlow() {
    delete (taxiStation);
    delete (map);
}

void MainFlow::createTripInfo() {
    int id, x_start, y_start, x_end, y_end, num_of_passenger;
    double tariff;
    char temp;
    //receiving trip details
    cin >> id >> temp >> x_start >> temp >> y_start >> temp >> x_end >> temp >> y_end >> temp
        >> num_of_passenger >> temp >> tariff;
    TripInfo *tripInfo = new TripInfo(id, x_start, y_start, x_end, y_end, num_of_passenger, tariff);
    taxiStation->addTrip(tripInfo);
}

void MainFlow::createVehicle() {
    int id, taxi_type;
    char manufacturer, color, temp;
    //receiving trip details
    cin >> id >> temp >> taxi_type >> temp >> manufacturer >> temp >> color;
    Taxi *taxi = new Taxi(id, manufacturer, color, taxi_type);
    taxiStation->addTaxi(taxi);
}

void MainFlow::requestDriverLocation() {
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

void MainFlow::startDriving() {
    taxiStation->driveAll();
}



