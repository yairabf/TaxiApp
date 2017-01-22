
#include <stack>
#include <map>
#include "Server.h"
#include "../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;

int numOfDrivers;
int numberOfThreads;

Server::Server(int columns, int rows, int portNumber):tcp(Tcp(1,portNumber)) {
    map = new Map(columns, rows);
    taxiStation = new TaxiStation(map);
    tcp.initialize();
    isFirst9 = true;
    LOG(INFO) << "Server initialize";
    pthread_mutex_init(&this->task_locker, 0);
    pthread_mutex_init(&this->driver_locker,0);
    pthread_mutex_init(&this->thread_locker,0);
    pthread_mutex_init(&this->numOfThreads_locker, 0);
    tasks = new list<ClientInfo*>;
}

Server::~Server() {
    delete (taxiStation);
    delete (map);
}

void Server::run() {
    int numberOfObstacles, x, y;
    char temp;
    LOG(INFO) << "how many obstacles?";
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
        int temp;
        LOG(INFO) << "enter Task";
        LOG(INFO) << this->taxiStation->getClock();
        cin >> temp;
        if(numberOfThreads == 0 || temp != 9 || temp != 7 ||isFirst9) {
            pthread_mutex_lock(&this->thread_locker);
            numberOfThreads = numOfDrivers;
            pthread_mutex_unlock(&this->thread_locker);
            task = temp;
            switch (task) {
                case 1:
                    LOG(INFO) << "server has started task 1";
                    createDriver();
                    break;
                case 2:
                    LOG(INFO) << "server has started task 2";
                    createTripInfo();
                    break;
                case 3:
                    LOG(INFO) << "server has started task 3";
                    createVehicle();
                    break;
                case 4:
                    LOG(INFO) << "server has started task 4";
                    requestDriverLocation();
                    break;
                case 7:
                {
                    LOG(INFO) << "server has started task 7";
                    pthread_mutex_lock(&this->task_locker);
                    list<ClientInfo *>::iterator tasksIter = tasks->begin();
                    while (tasksIter != tasks->end()) {
                        (*tasksIter)->task->push(7);
                        tasksIter++;
                    }
                    while (numberOfThreads != 0) {

                    }
                }
                tcp.~Tcp();
                    return;
                case 9:
                {
                    LOG(INFO) << "server has started task 9";
                    pthread_mutex_lock(&this->task_locker);
                    list<ClientInfo* >::iterator tasksIter = tasks->begin();
                    while (tasksIter != tasks->end()) {
                        (*tasksIter)->task->push(9);
                        tasksIter++;
                    }
                    pthread_mutex_unlock(&this->task_locker);
                    while (numberOfThreads != 0) {

                    }
                }
                    //taxiStation->advanceClock();
                    taxiStation->advanceClock();
                    break;
                default:
                    break;
            }
        }
    }  while (true);

}

void Server::createDriver() {
    /*receiving all the drivers and insert them into taxiStation list of drivers*/
    pthread_t clientThread;
    LOG(INFO) << "enter num of drivers";
    cin >> numOfDrivers;
    for(int i=0; i < numOfDrivers; i++) {
        ClientInfo* clientInfo = new ClientInfo();
        clientInfo->server = this;
        //creating a thread for a client
        pthread_create(&clientThread, NULL, Server::createThreadsForDrivers, clientInfo);
        LOG(INFO) << "server says: a thread has been created";
        numberOfThreads++;
        tasks->push_back(clientInfo);
    }

}

void Server::createTripInfo() {
    int id, x_start, y_start, x_end, y_end, num_of_passenger, start_time;
    double tariff;
    char temp;
    LOG(INFO) << "enter trip info: id, start,end,numof,tarrif,time";
    //receiving trip details
    cin >> id >> temp >> x_start >> temp >> y_start >> temp >> x_end >> temp >> y_end >> temp
        >> num_of_passenger >> temp >> tariff >> temp >> start_time;
    TripInfo *tripInfo = new TripInfo(id, x_start, y_start, x_end, y_end, num_of_passenger, tariff, start_time);
    taxiStation->addTrip(tripInfo);
}

void Server::createVehicle() {
    int id, taxi_type;
    char manufacturer, color, temp;
    LOG(INFO) << "enter taxi";
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

void Server::receivesDriverAndSendTaxi(int* clientDescriptor) {
    Driver* driver;
    char buffer[1024];
    //receiving descriptor of client port
    *clientDescriptor = tcp.acceptClient();
    //saving the client descriptor
    if(*clientDescriptor > 0) {
        tcp.reciveData(buffer, sizeof(buffer), *clientDescriptor);
        //de serializing the driver we have received.
        string stringedBuffer(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device((char *) stringedBuffer.c_str(), stringedBuffer.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> driver;
        LOG(INFO) << "the server received from client number: " << *clientDescriptor
                  << " the driver with id: " << driver->getId();
        //pthread_mutex_lock(&this->driver_locker);
        this->getTaxiStation()->addDriver(driver);
        //pthread_mutex_unlock(&this->driver_locker);
        Taxi *taxi;
        /*serialize the taxi we want to send the client*/
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        taxi = driver->getTaxi();
        oa << taxi;
        s.flush();
        tcp.sendData(serial_str, *clientDescriptor);
        LOG(INFO) << "server sent client number: " << *clientDescriptor
                  << " a taxi with id: " << taxi->getId();
    }
    else {
        LOG(INFO) << "error in accepting the client by the server ";
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
    LOG(INFO) << "server received from client number :" << client << " the driver id: " << id;
    //we have the correct trip info cos of assign drivers func
    Driver *driver = taxiStation->getDriverById(id);
    //assigning the correct trip if needed
    taxiStation->assignTripToDriver(driver);
    if(driver->getTripInfo() == NULL || driver->getTripInfo()->isDone()) {
        LOG(INFO) << "server says: driver from client: " << client
                  << " has trip info still null, not error. or his tripinfo done";
        //driving the driver if needed.
        tcp.sendData("none", client);
        LOG(INFO) << "server sent client number: " << client << " the string none";
    }
        //if this is not the first time we pressed 9 and the route is not empty and the time of the trip is now
        //so we want the client to drive to the next spot.
    else if((!isFirst9) &&
            (!driver->getTripInfo()->getRoute()->empty()) &&
            (driver->getTripInfo()->getStart_time() <= taxiStation->getClock())){
        taxiStation->driveOneDriver(driver);
        Node* node = driver->getLocation();
        string driversLocation = node->printValue();
        tcp.sendData("go", client);
        LOG(INFO) << "server sent client number: " << client << " the string go";
        //receiving a temp here to retain ping pong
        tcp.reciveData(buffer, sizeof(buffer), client);
        tcp.sendData(driversLocation, client);
        LOG(INFO) << "server sent client number: " << client << " the location: " << driversLocation;
        //if first 9
    } else {
        tcp.sendData("none", client);
        LOG(INFO) << "server sent client number: " << client << " the string none";
    }
}

void* Server::createThreadsForDrivers(void* inf) {
    ClientInfo* clientInfo = (ClientInfo*)inf;
    int task = 5;
    int clientDescriptor;
    clientInfo->server->receivesDriverAndSendTaxi(&clientDescriptor);
    do {
        if(clientInfo->task->size() > 0) {
            task = clientInfo->task->top();
            clientInfo->task->pop();
        }
        switch (task) {
            case 9:
                clientInfo->server->startDriving(clientDescriptor);
                clientInfo->server->map->resetVisited();
                clientInfo->server->isFirst9 = false;
                pthread_mutex_lock(&clientInfo->server->thread_locker);
                numberOfThreads--;
                pthread_mutex_unlock(&clientInfo->server->thread_locker);
                task = 5;
                break;
            case 7:
                clientInfo->server->tcp.sendData("finish", clientDescriptor);
                pthread_mutex_lock(&clientInfo->server->thread_locker);
                numberOfThreads--;
                pthread_mutex_unlock(&clientInfo->server->thread_locker);
                break;
            default:
                break;
        }
    } while (task != 7);
    //info was created by new in createDrivers() so we are deleting here.
    pthread_exit(NULL);
}



TaxiStation* Server::getTaxiStation() const {
    return taxiStation;
}

/**
 * The main method that runs the program, the method receives form the user the size of the grid
 * and the location of the start point and the goal and the method prints the the fastest route.
 */
int main(int argc, char** argv) {
    int columns, rows, portNumber;
    LOG(INFO) << "enter size of grid";
    cin >> columns;
    cin >> rows;
    portNumber = atoi(argv[1]);
    //need to change 5555 to portNumber
    Server server = Server(columns, rows, portNumber);
    server.run();
    return 1;
}


