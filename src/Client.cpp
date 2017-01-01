

#include <fstream>
#include "Client.h"
#include "Driver.h"
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

int main(){
    int id,age,exp,vid;
    char status,temp;
    cin >> id >> temp >> age >> temp >> status >> temp >> exp >> vid;
    ClientDriver clientDriver = ClientDriver(1111);
    clientDriver.createAndSendDriver(id,age,status,exp,vid);
}


ClientDriver::ClientDriver(int portNumber) : udp(Udp(0, portNumber)) {
    udp.initialize();
    cout << "hello from client";
}

int ClientDriver::createAndSendDriver(int id, int age, char status, int experience, int vehicle_id) {
    Driver *driver = new Driver(id, age, status, experience, vehicle_id);
    //serializing the driver and sending it.
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    udp.sendData(serial_str);

    //receiving the taxi from server and adding it to the driver
    Taxi *taxi;
    char buffer[1024];
    udp.reciveData(buffer, sizeof(buffer));
    //de serializing the taxi we have received.
    string stringedBuffer(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device((char *) stringedBuffer.c_str(), stringedBuffer.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> (taxi);
    driver->assignTaxi(taxi);


    while (true) {
        //receiving the trip info from the server and adding it to the driver
        TripInfo *tripInfo;
        char buffer2[1024];
        udp.reciveData(buffer2, sizeof(buffer2));
        string stringedBuffer2(buffer2, sizeof(buffer2));
        //if the server told us to finish
        if (stringedBuffer2 == "finish")
            break;
        //if the server wants to know our location
        else if (stringedBuffer2 == "location") {
            //udp.sendData(driver->getLocation()->printValue());
            boost::iostreams::back_insert_device<std::string> inserter1(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s3(inserter);
            boost::archive::binary_oarchive oa3(s);
            //sending the location
            oa << *driver->getLocation();
            s.flush();
            udp.sendData(serial_str);
        }
        else {
            boost::iostreams::basic_array_source<char> device2((char *) stringedBuffer2.c_str(),
                                                               stringedBuffer2.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device);
            boost::archive::binary_iarchive ia2(s3);
            ia2 >> tripInfo;
            driver->assignTripInfo(tripInfo);
            //check if it is ok to use buffer 2 again
            //drives as long as it receives go
            while (true) {
                udp.reciveData(buffer2, sizeof(buffer2));
                string stringedBufferDrive(buffer2, sizeof(buffer2));
                if (stringedBuffer2 == "go")
                    driver->drive();
                if (driver->getTripInfo()->getRoute()->empty()) {
                    break;
                }
            }
        }
    }
    udp.~Udp();
}
