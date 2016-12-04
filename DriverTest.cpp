#include "gtest/gtest.h"
#include "Driver.h"
#include "NodeBlock.h"
#include "BreadthFirstSearch.h"
#include "Map.h"

using namespace std;

class DriverTest: public ::testing::Test{
protected:
    Driver driver;
    virtual void SetUp() {
        cout << "Setting Up" << endl;
    }

    virtual void TearDown(){
        cout << "Tearing Down" << endl;
    }

public:
    DriverTest():driver(305263501, 26, 5, "married"){};
};


TEST_F(DriverTest, YearsOfExpTest) {
    ASSERT_TRUE(driver.getYearsExp() >= 0) << "experience is negative";
    ASSERT_EQ(driver.getYearsExp(), 5) << "experience wasn't construct well";
    driver.setYearsExp(10);
    ASSERT_EQ(driver.getYearsExp(), 10) << "experience wasn't set well";
}

TEST_F(DriverTest, OccupiedTest) {
    ASSERT_FALSE(driver.isOccupied()) << "occupation wasn't construct well";
    driver.setOccupied(true);
    ASSERT_TRUE(driver.isOccupied()) << "occupation wasn't set well";
}


TEST_F(DriverTest, AvgSatisfactionTest) {
    ASSERT_EQ(driver.getAvgSatisfaction(),0) << "Average satisfaction wasn't construct well";
    driver.setAvgSatisfaction(4.4);
    ASSERT_TRUE(driver.getAvgSatisfaction() - 4.4 < 0.00001 ) << "Average satisfaction wasn't set well";
}

TEST_F(DriverTest, LocationTest) {
    Node* loc = new NodeBlock(Point(5,4));
    driver.setLocation(loc);
    EXPECT_EQ(driver.getLocation(), loc) << " Driver location wasn't set well";
    delete (loc);
}

TEST_F(DriverTest, TaxiTest) {
    Taxi taxi(1111,50,"fiat","black",1,5.00);
    driver.assignTaxi(&taxi);
    ASSERT_EQ(driver.getTaxi(), &taxi) << "Taxi wasn't set right";
}

TEST_F(DriverTest, AddPassengerTest){
    Passenger passenger1(Point(0,0),Point(5,5));
    Passenger passenger2(Point(5,6),Point(1,2));
    driver.addPassenger(&passenger1);
    driver.addPassenger(&passenger2);
    ASSERT_TRUE(driver.passengerIsExist(&passenger1)) << "passenger isn't exist";
    ASSERT_TRUE(driver.passengerIsExist(&passenger2)) << "passenger isn't exist";
}

TEST_F(DriverTest, DriveTest) {
    Map map(10,10);
    BreadthFirstSearch bfs(&map);
    NodeBlock* start = map.getBlock(Point(2,2));
    NodeBlock* end = map.getBlock(Point(5,6));
    stack<Node*> route = bfs.breadthFirstSearch(start, end);
    driver.drive(&route);
    ASSERT_EQ(driver.getLocation(),end) << "driver wasn't drive to correct location";
}

TEST_F(DriverTest, CalculatePriceTest) {
    Taxi taxi(1111,50,"fiat","black",1,5.00);
    driver.assignTaxi(&taxi);
    float price = driver.calculatePrice(10);
    ASSERT_EQ(price, 50.0) << "Price wan't calculated correctly";
}

