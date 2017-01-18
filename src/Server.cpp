#include "Server.h"
#include "Tcp.h"
#include "InfoForClientThread.h"

Server::Server(int columns, int rows, int portNumber):tcp(Tcp(1,portNumber)) {
    map = new Map(columns, rows);
    taxiStation = new TaxiStation(map);
    //clock = 0;
    tcp.initialize();
    isFirst9 = true;
    pthread_mutex_init(&this->task_locker, 0);
}


void Server::run() {
    int numberOfObstacles, x, y;
    char temp;
    cout << "how many obstacles?" << endl;
    cin >> numberOfObstacles;
    if(numberOfObstacles > 0 ) {
        //waits for obstacles input
        //need to add a test that checks if the obstacles have been inserted correctly.
        for(int i = 1; i <= numberOfObstacles; i++) {
            cin >> x >> temp >> y;
            taxiStation->setObstacle(x, y);
        }
    }
    do {
        cout << "enter task" << endl;
        pthread_mutex_lock(&this->task_locker);
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
            case 9:
                taxiStation->advanceClock();
                break;
            case 7:
                tcp.sendData("finish", 7);
                tcp.~Tcp();
                return;
            default:
                break;
        }
        pthread_mutex_unlock(&this->task_locker);
    }  while (true);

}

void Server::createDriver() {
    /*receiving all the drivers and insert them into taxiStation list of drivers*/
    int numOfDrivers;
    pthread_t clientThread;
    cout << "enter num of drivers" << endl;
    cin >> numOfDrivers;
    for(int i=0; i < numOfDrivers; i++) {
        //creating a thread for a client
        InfoForClientThread* info = new InfoForClientThread(&task, this);
        pthread_create(&clientThread, NULL, Server::createThreadsForDrivers, info);
    }
    /*int id, age, experience, vehicle_id;
    char status , temp;
    //receiving driver details
    cin >> id >> temp >> age >> temp >> status >> temp >> experience >> temp >> vehicle_id;
    Driver* driver = new Driver(id,age,status,experience,vehicle_id);
    taxiStation->addDriver(driver);*/

    //need to create a port and send it to the ClientDriver
    //ClientDriver clientDriver(;//need to add a port number.
}

void* Server::createThreadsForDrivers(void* inf) {
    InfoForClientThread* info = (InfoForClientThread*)inf;
    int task;
    int clientDescriptor = info->getClientDescriptor();
    Server* server = info->getServer();
    server->receivsDriverAndSendTaxi(info);
    do {
        task = server->task;
        switch (task) {
            case 9:
                server->startDriving(clientDescriptor);
                server->map->resetVisited();
                server->isFirst9 = false;
                break;
            case 7:
                server->tcp.sendData("finish", 7);
                server->tcp.~Tcp();
                break;
            default:
                break;
        }
    } while (task != 7);
    //info was created by new in createDrivers() so we are deleting here.
    delete(info);
}


Server::~Server() {
    delete (taxiStation);
    delete (map);
}

void Server::createTripInfo() {
    int id, x_start, y_start, x_end, y_end, num_of_passenger, start_time;
    double tariff;
    char temp;
    cout << "enter trip info: id, start,end,numof,tarrif,time" << endl;
    //receiving trip details
    cin >> id >> temp >> x_start >> temp >> y_start >> temp >> x_end >> temp >> y_end >> temp
        >> num_of_passenger >> temp >> tariff >> temp >> start_time;
    TripInfo *tripInfo = new TripInfo(id, x_start, y_start, x_end, y_end, num_of_passenger, tariff, start_time);
    taxiStation->addTrip(tripInfo);
}

void Server::createVehicle() {
    int id, taxi_type;
    char manufacturer, color, temp;
    cout << "enter taxi" << endl;
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

void Server::startDriving(int client) {
    char buffer[1024];
    int id;
    //receiving the id
    tcp.reciveData(buffer, sizeof(buffer), client);
    string stringedBuffer(buffer, sizeof(buffer));
    istringstream convert(stringedBuffer);
    //give the value to id using the characters in the stream
    if ( !(convert >> id) )
        id = -1;
    //we have the correct trip info cos of assign drivers func
    Driver *driver = taxiStation->getDriverById(id);
    //assigning the correct trip if needed
    taxiStation->assignTripToDriver(driver);
    //driving the driver if needed.
    taxiStation->driveOneDriver(driver);
    //if this is not the first time we pressed 9 and the route is not empty and the time of the trip is now
    //so we want the client to drive to the next spot.
    if((!isFirst9) &&
            (!driver->getTripInfo()->getRoute()->empty()) &&
            (driver->getTripInfo()->getStart_time() <= taxiStation->getClock())){
        //driver->drive();
        Node* node = driver->getLocation();
        string driversLocation = node->printValue();
        tcp.sendData("go", client);
        //receiving a temp here to retain ping pong
        tcp.reciveData(buffer, sizeof(buffer), client);
        tcp.sendData(driversLocation, client);
        //if first 9
    } else
        tcp.sendData("none", client);
}

TaxiStation* Server::getTaxiStation() const {
    return taxiStation;
}

Tcp* Server::getTcp() {
    return &tcp;
}

int Server::getTask() {
    return task;
}

void Server::receivsDriverAndSendTaxi(InfoForClientThread* info) {
    Driver* driver;
    char buffer[1024];
    int client;
    //receiving descriptor of client port
    client = tcp.acceptClient();
    //saving the client descriptor
    info->setClientDescriptor(client);
    if(client > 0) {
        tcp.reciveData(buffer, sizeof(buffer), client);
        //de serializing the driver we have received.
        string stringedBuffer(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device((char *) stringedBuffer.c_str(), stringedBuffer.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> driver;
        //cout << driver->getId();
        this->getTaxiStation()->addDriver(driver);

        Taxi *taxi;
        /*serialize the taxi we want to send the client*/
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        taxi = driver->getTaxi();
        oa << taxi;
        s.flush();
        tcp.sendData(serial_str, client);
    }
    else {
        cout << "error in accepting the client by the server " << endl;
    }
}

/**
 * The main method that runs the program, the method receives form the user the size of the grid
 * and the location of the start point and the goal and the method prints the the fastest route.
 */
int main(int argc, char** argv) {
    int columns, rows, portNumber;
    cout << "enter size of grid" << endl;
    cin >> columns;
    cin >> rows;
    portNumber = *argv[1] - '0';
    //need to change 5555 to portNumber
    Server server = Server(columns, rows, 1145);
    server.run();
    return 1;
}


