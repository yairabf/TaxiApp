
#include <stack>
#include <map>
#include "Server.h"
#include "InputValidityTests.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;

int numOfDrivers;
int numberOfThreads;

Server::Server(int columns, int rows, int portNumber):tcp(Tcp(1,portNumber)) {
    map = new Map(columns, rows);
    taxiStation = new TaxiStation(map);
    tcp.initialize();
    isFirst9 = true;
    //clientInfo.task = new stack<int>;
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
    list<ClientInfo *>::iterator tasksIter = tasks->begin();
    while (tasksIter != tasks->end()) {
        ClientInfo* clientInfo = *tasksIter;
        delete(clientInfo->task);
        delete(*tasksIter);
        tasksIter++;
    }
    delete(tasks);
}

void Server::run() {

    do {
        int tempInt;
        string input;
        LOG(INFO) << "enter Task";
        LOG(INFO) << this->taxiStation->getClock();
        getline(cin, input);
        if(input.find_first_not_of("123479") != string::npos) {
            cout << "-1" << endl;
            continue;
        } else {
            tempInt = stoi(input);
        }
        pthread_mutex_lock(&this->thread_locker);
        numberOfThreads = numOfDrivers;
        pthread_mutex_unlock(&this->thread_locker);
        task = tempInt;
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
                while(!taxiStation->getThreadPool()->isEmpty()){

                }
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
                cout << "-1" << endl;
                break;
        }
    }  while (true);

}


void Server::createDriver() {
    /*receiving all the drivers and insert them into taxiStation list of drivers*/
    pthread_t clientThread;
    string input;
    numOfDrivers = 0;
    LOG(INFO) << "enter num of drivers";
    getline(cin, input);
    if(input.find_first_not_of("0123456789") != string::npos) {
        cout << "-1" << endl;
    } else {
        numOfDrivers = stoi(input);
        if(numOfDrivers == 0)
            cout << "-1" << endl;
    }
    //if the input is invalid the numOfDrivers will stay 0 and the for loop will not execute
    for(int i=0; i < numOfDrivers; i++) {
        ClientInfo* clientInfo = new ClientInfo();
        clientInfo->server = this;
        clientInfo->task = new stack<int>;
        //creating a thread for a client
        pthread_create(&clientThread, NULL, Server::createThreadsForDrivers, clientInfo);
        LOG(INFO) << "server says: a thread has been created";
        numberOfThreads++;
        tasks->push_back(clientInfo);
    }

}


void Server::createTripInfo() {
    int id, x_start, y_start, x_end, y_end, num_of_passenger, start_time;
    string input;
    double tariff;
    LOG(INFO) << "enter trip info: id, start,end,numof,tarrif,time";
    //receiving trip details
    getline(cin, input);
    InputValidityTests ivt;
    vector<string> v = ivt.inputBraker(input, ",");
    //if there is enough parameters we can continue the check
    if(v.size() == 8) {
        if(tripInfoInputValid(v)) {
            id = stoi(v[0]);
            x_start = stoi(v[1]);
            y_start = stoi(v[2]);
            x_end = stoi(v[3]);
            y_end = stoi(v[4]);
            num_of_passenger = stoi(v[5]);
            tariff = stod(v[6]);
            start_time = stoi(v[7]);
            TripInfo *tripInfo = new TripInfo(id, x_start, y_start, x_end, y_end,
                                              num_of_passenger, tariff, start_time);
            taxiStation->addTrip(tripInfo);
        } else
            cout << "-1" << endl;
    } else
        cout << "-1" << endl;
}

bool Server::tripInfoInputValid(vector<string> v) {
    int x_start, y_start, x_end, y_end;
    if(v[0].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(v[1].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(v[2].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(v[3].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(v[4].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(v[5].find_first_not_of("0123456789") != string::npos)
        return false;
        //added '.' cos this is tarrif and can be float
    else if(v[6].find_first_not_of("0123456789.") != string::npos)
        return false;
    else if(v[7].find_first_not_of("0123456789") != string::npos)
        return false;
    x_start = stoi(v[1]);
    y_start = stoi(v[2]);
    x_end = stoi(v[3]);
    y_end = stoi(v[4]);
    if(x_start >= taxiStation->getColumns() || x_end >= taxiStation->getColumns()
            || y_start >= taxiStation->getRows() || y_end >= taxiStation->getRows())
        return false;
    else
        return true;
}

void Server::createVehicle() {
    int id, taxi_type;
    string input;
    char manufacturer, color;
    InputValidityTests ivt;
    LOG(INFO) << "enter taxi";
    //receiving trip details
    getline(cin, input);
    vector<string> v = ivt.inputBraker(input, ",");
    if(v.size() == 4) {
        if(taxiInputValid(v)) {
            id = stoi(v[0]);
            taxi_type = stoi(v[1]);
            manufacturer = v[2].at(0);
            color = v[3].at(0);
            Taxi *taxi = new Taxi(id, manufacturer, color, taxi_type);
            taxiStation->addTaxi(taxi);
        } else
            cout << "-1" << endl;
    } else
        cout << "-1" << endl;
}

bool Server::taxiInputValid(vector<string> v) {
    if(v[0].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(!(!v[1].compare("1") || !v[1].compare("2")))
        return false;
        //compares returns 0 if equal. not on that is 1. not on all is 0.
        //if i get 1 then none of them are equal so false
    else if(!(!v[2].compare("H") || !v[2].compare("F") || !v[2].compare("S") || !v[2].compare("T")))
        return false;
    else if(!(!v[3].compare("R") || !v[3].compare("B") || !v[3].compare("P") ||
            !v[3].compare("W") || !v[3].compare("G")))
        return false;
    else
        return true;
}

void Server::requestDriverLocation() {
    int id;
    string input;
    bool driverExists = false;
    LOG(INFO) << "enter driver id";
    getline(cin, input);
    if(input.find_first_not_of("0123456789") != string::npos)
        cout << "-1" << endl;
    else {
        id = stoi(input);
        list<Driver*>::iterator it = taxiStation->getDrivers()->begin();
        while(it != taxiStation->getDrivers()->end()) {
            if(it.operator*()->getId() == id) {
                cout << it.operator*()->getLocation()->printValue() << endl;
                driverExists = true;
                break;
            }
            it++;
        }
        //if the driver id is incorrect
        if(!driverExists)
            cout << "-1" << endl;
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
    //ClientInfo* clientInfo = clientInfo1->server->clientInfo;
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
    int columns, rows, numberOfObstacles, x, y, portNumber;
    bool valid;
    string input;
    portNumber = atoi(argv[1]);
    vector<string> v;
    InputValidityTests ivt;
    //making sure the grid size is valid
    Server* server;
    while(true) {
        LOG(INFO) << "enter size of grid";
        getline(cin, input);
        //breaking the string in to columns and rows
        v = ivt.inputBraker(input, " ");
        if(v.size() != 2) {
            cout << "-1" << endl;
            continue;
            //if one of the grid sizes is not a number
        } else if((v[0].find_first_not_of("0123456789") != string::npos) ||
                (v[1].find_first_not_of("0123456789") != string::npos)) {
            cout << "-1" << endl;
            continue;
        } else {
            //we know columns and rows are numbers. checking if 0, negative has been checked
            columns = stoi(v[0]);
            rows = stoi(v[1]);
            if(rows == 0 || columns == 0) {
                cout << "-1" << endl;
                continue;
            } else {
                //******************************sd***************need to check how far down a mistake means to start over,
                // ********************************************whenever i do so before a continue i need to delete server
                server = new Server(columns, rows, portNumber);
                LOG(INFO) << "how many obstacles?";
                getline(cin, input);
                input = ivt.trim(input);
                //making sure number of obstacles is a number
                if(input.find_first_not_of("0123456789") != string::npos) {
                    cout << "-1" << endl;
                    delete(server);
                    continue;
                } else {
                    valid = true;
                    //number of obstacles is a number
                    numberOfObstacles = stoi(input);
                    if (numberOfObstacles >= 0) {
                        for (int i = 0; i < numberOfObstacles; i++) {
                            //checks if the obstacles are in grid
                            LOG(INFO) << "enter obstacle" ;
                            getline(cin, input);
                            v = ivt.inputBraker(input, ",");
                            //if there arent enough parameters
                            if(v.size() != 2) {
                                valid = false;
                                break;
                                //if they arent numbers
                            } else if((v[0].find_first_not_of("0123456789") != string::npos) ||
                               (v[1].find_first_not_of("0123456789") != string::npos)) {
                                valid = false;
                                break;
                            } else {
                                x = stoi(v[0]);
                                y = stoi(v[1]);
                                //if they are out of the grid
                                if (x >= columns || y >= rows) {
                                    valid = false;
                                    break;
                                    //if the obstacles are valid we add them
                                } else
                                    server->setObstacle(x, y);
                            }
                        }
                        //if one of the obstacles input was incorrect
                        if(!valid) {
                            cout << "-1" << endl;
                            delete(server);
                            continue;
                            //if all input was valid we start the program
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
    server->run();
    delete(server);
    return 1;
}

void Server::setObstacle(int x, int y) {
    taxiStation->setObstacle(x,y);
}



