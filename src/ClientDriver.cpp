//
// Created by hanani on 26/12/16.
//

#include <fstream>
#include "ClientDriver.h"
#include "Driver.h"
#include "boost"

ClientDriver::ClientDriver(int portNumber) {
    udp = Udp(0, portNumber);
    udp.initialize();
}

int ClientDriver::createAndSendDriver(int id, int age, char status, int experience, int vehicle_id) {
    Driver* driver = new Driver(id,age,status,experience,vehicle_id);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    udp.sendData(serial_str);
    char buffer[1024];
    udp.reciveData(buffer, sizeof(buffer));

}
