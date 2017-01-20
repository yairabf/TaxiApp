

#include <fstream>
#include "Client.h"
#include "Driver.h"
#include "NodeBlock.h"
#include "../easylogging++.h"

INITIALIZE_EASYLOGGINGPP
//
int main(int argc, char** argv){
    int id, age, exp, vid, portNumber;
    string ip;
    char status,temp;
    //cout << "enter driver" << endl;
    cin >> id >> temp >> age >> temp >> status >> temp >> exp >> temp>> vid;
    ip = argv[1];
    //portNumber = *argv[2] - '0';
    //need to change 5555 to portNumber
    ClientDriver clientDriver = ClientDriver(1145, "127.0.0.1");
    clientDriver.createAndSendDriver(id,age,status,exp,vid);
    return 0;
}


ClientDriver::ClientDriver(int portNumber, string ip) : tcp(Tcp(0, portNumber)) {
    tcp.initialize();
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
    LOG(INFO) << "client sent driver with id: " << driver->getId() << endl;

    //receiving the taxi from server and adding it to the driver
    Taxi *taxi;
    char buffer[1024];
    tcp.reciveData(buffer, sizeof(buffer), 1);
    //de serializing the taxi we have received.
    string stringedBuffer(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device((char *) stringedBuffer.c_str(),
                                                      stringedBuffer.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> taxi;
    driver->assignTaxi(taxi);
    LOG(INFO) << "client has assigned taxi with id: " << driver->getTaxi()->getId() << endl;
    NodeBlock* driverLoc;
    Point* pointLocation = new Point(0,0);
    while (true) {
        char buffer2[1024];
        //sending the id of the driver
        string stringedId;
        ostringstream convert;
        convert << driver->getId();
        stringedId = convert.str();
        tcp.sendData(stringedId, 1);
        LOG(INFO) << "client send driver id: " << stringedId << endl;
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
            if(driverLoc!= NULL)
                delete(driverLoc);
            driverLoc = new NodeBlock(*pointLocation);
            driver->setLocation(driverLoc);
            LOG(INFO) << "client location changed to: " << driver->getLocation()->printValue() << endl;
        } /*else if (strcmp(goOrFinish.data(), "none") == 0) {
            cout << "client received message: none" << endl;
            continue;
        }*/
            //if we need to finish
        else if(strcmp(goOrFinish.data(), "finish") == 0)
            break;
        else
            continue;
    }
    LOG(INFO) << "client starting deletion of pointers after while loop" << endl;
    tcp.~Tcp();
    delete(pointLocation);
    delete(driverLoc);
    delete(driver->getTaxi());
    delete(driver);
}

