
#include <gtest/gtest.h>
#include "TaxiStation.h"

using namespace std;
class TaxiStationTest: public ::testing::Test {
public:
    TaxiStation *taxiStation;
    Map* map1;
protected:
    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<< endl;
        Map* map1 = new Map(10,10);
        taxiStation = new TaxiStation(map1);
    }

    virtual void TearDown () {
        cout<<"tearing down" << endl;
        delete(taxiStation);
        delete(map1);
    }

public:
    TaxiStationTest(){};
};

TEST_F(TaxiStationTest, addDriverTest) {
    Driver* driver = new Driver(1111,23,5,"married");
    taxiStation->addDriver(driver);
    ASSERT_TRUE(taxiStation->doesDriverExist(driver)) << "Driver wasn't added";
    delete(driver);
}

TEST_F(TaxiStationTest, removeDriverTest) {
    Driver* driver = new Driver(1111,23,5,"married");
    taxiStation->addDriver(driver);
    taxiStation->removeDriver(driver);
    ASSERT_FALSE(taxiStation->doesDriverExist(driver)) << "Driver wasn't removed";
    delete(driver);

}

TEST_F(TaxiStationTest, addTaxiTest) {
    Taxi* taxi = new Taxi(1111,50,"fiat","black",1,5.00);
    taxiStation->addTaxi(taxi);
    ASSERT_TRUE(taxiStation->doesTaxiExist(taxi)) << "Driver wasn't added";
    delete(taxi);

}

TEST_F(TaxiStationTest, removeTaxiTest) {
    Taxi* taxi = new Taxi(1111,50,"fiat","black",1,5.00);
    taxiStation->addTaxi(taxi);
    taxiStation->removeTaxi(taxi);
    ASSERT_FALSE(taxiStation->doesTaxiExist(taxi)) << "Driver wasn't removed";
    delete(taxi);

}