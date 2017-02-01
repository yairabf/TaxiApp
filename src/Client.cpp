

#include <fstream>
#include "Client.h"
#include "Driver.h"
#include "NodeBlock.h"
#include "../easylogging++.h"
#include "InputValidityTests.h"

_INITIALIZE_EASYLOGGINGPP
//
int main(int argc, char** argv){
    int id, age, exp, vid, portNumber;
    string ip, input;
    LOG(INFO)<< "enter driver";
    getline(cin, input);
    ip = argv[1];
    portNumber = atoi(argv[2]);
    InputValidityTests ivt;
    vector<string> v = ivt.inputBraker(input, ",");
    if(v.size() == 5) {
        if(ClientDriver::driverInputValid(v)) {
            id = stoi(v[0]);
            age = stoi(v[1]);
            exp = stoi(v[3]);
            vid = stoi(v[4]);
            ClientDriver clientDriver = ClientDriver(portNumber, ip);
            clientDriver.createAndSendDriver(id, age, v[2].at(0), exp, vid);
        }
    }
    return 0;
}


bool ClientDriver::driverInputValid(vector<string> v) {
    if(v[0].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(v[1].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(!(!v[2].compare("M") || !v[2].compare("D") || !v[2].compare("W") || !v[2].compare("S")))
        return false;
    else if(v[3].find_first_not_of("0123456789") != string::npos)
        return false;
    else if(v[4].find_first_not_of("0123456789") != string::npos)
        return false;
    return true;
}


ClientDriver::ClientDriver(int portNumber, string ip) : tcp(Tcp(0, portNumber)) {
    tcp.initialize();
    tcp.setIp(ip);
}

int ClientDriver::createAndSendDriver(int id, int age, char status, int experience,
                                      int vehicle_id) {
    Driver *driver = new Driver(id, age, status, experience, vehicle_id);
    //serializing the driver and sending it.
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    tcp.sendData(serial_str, 1);
    LOG(INFO) << "client sent driver with id: " << driver->getId();
    //receiving the taxi from server and adding it to the driver
    Taxi *taxi;
    char buffer[1024];
    tcp.reciveData(buffer, sizeof(buffer), 1);
    //de serializing the taxi we have received
    string stringedBuffer(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device((char *) stringedBuffer.c_str(),
                                                      stringedBuffer.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> taxi;
    driver->assignTaxi(taxi);
    LOG(INFO) << "client has assigned taxi with id: " << driver->getTaxi()->getId();
    Point* pointLocation = new Point(0,0);
    NodeBlock* driverLoc = new NodeBlock(*pointLocation);
    while (true) {
        char buffer2[1024];
        //sending the id of the driver
        string stringedId;
        ostringstream convert;
        convert << driver->getId();
        stringedId = convert.str();
        tcp.sendData(stringedId, 1);
        LOG(INFO) << "client send driver id: " << stringedId;
        //receiving go or finish
        tcp.reciveData(buffer2, sizeof(buffer2), 1);
        string goOrFinish = buffer2;
        if (strcmp(goOrFinish.data(), "go") == 0) {
            //sending to retain ping pong
            tcp.sendData("ok", 1);
            //receiving a node as a string but is actually point.toString
            tcp.reciveData(buffer2, sizeof(buffer2), 1);
            string stringedPoint = buffer2;
            pointLocation->pointFromString(stringedPoint);
            delete(driverLoc);
            driverLoc = new NodeBlock(*pointLocation);
            driver->setLocation(driverLoc);
            LOG(INFO) << "client location changed to: " << driver->getLocation()->printValue();
        }
        else if (strcmp(goOrFinish.data(), "none") == 0) {
            LOG(INFO) << "client received message: none";
            continue;
        }
            //if we need to finish
        else if(strcmp(goOrFinish.data(), "finish") == 0)
            break;
        else
            continue;
    }
    LOG(INFO) << "client starting deletion of pointers after while loop";
    delete(pointLocation);
    delete(driverLoc);
    delete(driver->getTaxi());
    delete(driver);
}

