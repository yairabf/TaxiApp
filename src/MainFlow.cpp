

#include "MainFlow.h"

MainFlow::MainFlow(const int columns, const int rows): map(Map(columns, rows)){
    taxiStation = TaxiStation(&map);
}

void MainFlow::run() {
    cout <<"please insert number of obstacles" << endl;
    int i, numberOfObstacles, x, y;
    cin >> numberOfObstacles;
    if(numberOfObstacles > 0 ) {
        //waits for obstacles input
        cout << "please enter points" << endl;
        //need to add a test that checks if the obstacles have been inserted correctly.
        for(i = 1; i <= numberOfObstacles; i++) {
            cin >> x >> y;
            taxiStation.setObstacle(x, y);
        }
    }
    cout << "Please insert task number" << endl;
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
                break;
            default:
                break;
        }
    }  while (task != 7);
}

void MainFlow::createDriver() {
    int id, age, experience, vehicle_id;
    char status , temp;
    cout << "Please insert a driver details" << endl;

    //receiving driver detail
    cin >> id >> temp >> age >> temp >> status >> temp >> experience >> temp >> vehicle_id;
    Driver* driver = new Driver(id,age,status,experience,vehicle_id);
    taxiStation.addDriver(driver);
}

MainFlow::~MainFlow() {

}

void MainFlow::createTripInfo() {
    int id, x_start, y_start, x_end, y_end, num_of_passenger, tariff;
    char temp;
    cout << "Please insert a trip details" << endl;

    //receiving trip details
    cin >> id >> temp >> x_start >> temp >> y_start >> temp >> x_end >> temp >> y_end >> temp
        >> num_of_passenger >> temp >> tariff;
    TripInfo tripInfo = TripInfo(id, x_start, y_start, x_end, y_end, num_of_passenger, tariff);
    taxiStation.addTrip(&tripInfo);
}

void MainFlow::createVehicle() {
    int id, taxi_type;
    char manufacturer, color, temp;
    cout << "Please insert a vehicle details" << endl;

    //receiving trip details
    cin >> id >> temp >> taxi_type >> temp >> manufacturer >> temp >> color;
    Taxi taxi = Taxi(id, manufacturer, color, taxi_type);
    taxiStation.addTaxi(&taxi);
}

void MainFlow::requestDriverLocation() {
    int id;
    cout << "Please insert a driver id" << endl;
    cin >> id;
    list<Driver*>::iterator it = taxiStation.getDrivers()->begin();
    while(it != taxiStation.getDrivers()->end()) {
        if(it.operator*()->getId() == id) {
            cout << it.operator*()->getLocation()->printValue();
            break;
        }
        it++;
    }
}

void MainFlow::startDriving() {
    taxiStation.driveAll();
}



