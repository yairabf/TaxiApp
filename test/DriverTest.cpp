#include "gtest/gtest.h"
#include "../src/Driver.h"
#include "../src/NodeBlock.h"
#include "../src/BreadthFirstSearch.h"
#include "../src/Map.h"

using namespace std;

/**
 * A driver test that check all the functionality of the driver works.
 */
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
    DriverTest():driver(305263501, 26, 'M', 4, 1243){};
};

/**
 * the test check if the setter of the location of the driver by receiving a node
 * object is working.
 */
TEST_F(DriverTest, LocationTest) {
    Node* loc = new NodeBlock(Point(5,4));
    driver.setLocation(loc);
    EXPECT_EQ(driver.getLocation(), loc) << " Driver location wasn't set well";
    delete (loc);
}

/**
 * the test check if the assignTaxi which assigns taxi for the driver works.
 */
TEST_F(DriverTest, TaxiTest) {
    Taxi taxi(1111,1,'F','B');
    driver.assignTaxi(&taxi);
    ASSERT_EQ(driver.getTaxi(), &taxi) << "Taxi wasn't set right";
}

/**
 * the test checks if the method addPassenger witch adds passengers to the
 * list of passengers that the driver holds, works,
 */
TEST_F(DriverTest, AddPassengerTest){
    Passenger passenger1(Point(0,0),Point(5,5));
    Passenger passenger2(Point(5,6),Point(1,2));
    driver.addPassenger(&passenger1);
    driver.addPassenger(&passenger2);
    ASSERT_TRUE(driver.passengerIsExist(&passenger1)) << "passenger isn't exist";
    ASSERT_TRUE(driver.passengerIsExist(&passenger2)) << "passenger isn't exist";
}

/**
 * the test check if the method drive works.
 * the test create a route by using the bfs and the send it to the driver.
 * if the driver location will be at the destination point at the end of the drive it means that
 * the test passed
 */
TEST_F(DriverTest, DriveTest) {
    Map map(10,10);
    BreadthFirstSearch bfs(&map);
    NodeBlock* start = map.getBlock(Point(2,2));
    NodeBlock* end = map.getBlock(Point(5,6));
    stack<Node*> route = bfs.breadthFirstSearch(start, end);
    TripInfo tripInfo(0,0, 0, 5, 5, 1, 2.00);
    tripInfo.setRoute(&route);
    driver.drive();
    ASSERT_EQ(driver.getLocation(),end) << "driver wasn't drive to correct location";
}

/**
 * the test check if the method that responsible for calculating the price after
 * a drive is working.
 */
TEST_F(DriverTest, CalculatePriceTest) {
    Taxi taxi(1111,1,'F','B');
    driver.assignTaxi(&taxi);
    double price = driver.calculatePrice(10);
    ASSERT_EQ(price, 50.0) << "Price wan't calculated correctly";
}

