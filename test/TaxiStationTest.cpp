
#include <gtest/gtest.h>
#include "../src/TaxiStation.h"

using namespace std;
class TaxiStationTest: public ::testing::Test {
public:
    TaxiStation *taxiStation;
    Taxi* taxi;
    Driver* driver;
    Map* map1;
    Node* farLocation;
protected:
    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<< endl;
        map1 = new Map(10,10);
        taxiStation = new TaxiStation(map1);
        taxi = new Taxi(1111,50,"fiat","black",1,5.00);
        taxiStation->addTaxi(taxi);
        driver = new Driver(1111,23,5,"married");
        //setting the location like this for the answerCallTest
        farLocation = map1->getBlock(Point(3,3));
        driver->setLocation(farLocation);
        taxiStation->addDriver(driver);
    }

    virtual void TearDown () {
        cout<<"tearing down" << endl;
        delete(taxiStation);
        //delete(map1);
        //delete(driver);
        //delete(taxi);
    }

public:
    bool areStacksEqual(stack<Node*> *stack1, stack<Node*> *stack2) {
        int i = 1;
        if(stack2 == NULL) return false;
        while (!stack1->empty()) {
            if(stack1->top() != stack2->top()) {
                return false;
            }
            stack1->pop();
            stack2->pop();
            i++;
        }
        return true;
    }
};

TEST_F(TaxiStationTest, addDriverTest) {
    ASSERT_TRUE(taxiStation->doesDriverExist(driver)) << "Driver wasn't added";
}

TEST_F(TaxiStationTest, removeDriverTest) {
    taxiStation->removeDriver(driver);
    ASSERT_FALSE(taxiStation->doesDriverExist(driver)) << "Driver wasn't removed";
}

TEST_F(TaxiStationTest, addTaxiTest) {
    ASSERT_TRUE(taxiStation->doesTaxiExist(taxi)) << "Driver wasn't added";
}

TEST_F(TaxiStationTest, removeTaxiTest) {
    taxiStation->removeTaxi(taxi);
    ASSERT_FALSE(taxiStation->doesTaxiExist(taxi)) << "Driver wasn't removed";
}
/**
 * these following tests check a method that operates this way:
 * it receives a passenger and a point of the passengers place.
 * it runs the bfs algorithm for all drivers from their location to the passengers'
 * location, using a private method, sends the correct driver to the passengers' location,
 * (using a different private method) and returns the driver to the taxi station.
 * the taxi satation creates a trip info and runs the bfs algorithm to create a route(as a stack)
 * and sends the trip info to the driver.
 * we will run a few tests to check these private methods aswell.
 *
 */
TEST_F(TaxiStationTest, answerCallTest1) {
    NodeBlock *passengerLocation = map1->getBlock(Point(0,0));
    NodeBlock *destination = map1->getBlock(Point(5,5));
    BreadthFirstSearch *bfs = new BreadthFirstSearch(map1);
    Passenger *passenger = new Passenger(Point(0,0), Point(5,5));
    //gets the correct route that the bfs generates
    stack<Node *> correctRoute = bfs->breadthFirstSearch(passengerLocation, destination);
    taxiStation->answerCall(Point(5,5), passenger);
    //checks if the driver has the correct route
    /*this loop will fail for segmentation fault since we dont actually have a route for the driver
     * however, since we have only one driver in the list of "taxi station" then once we run this
     * method this driver will definitely be assigned and therefore this test should work once we
     * receive the correct parameters.*/
    ASSERT_FALSE(driver->getTripInfo() == NULL) <<"the driver has no trip info"<<endl;
    stack<Node *> *driversRoute = driver->getTripInfo()->getRoute();
    EXPECT_TRUE(areStacksEqual(&correctRoute, driversRoute)) << "stacks are not eqaul" << endl;
    /*checks if the driver drove to the passenger, meaning if he got to the location
     * of the passenger*/
    EXPECT_EQ(passengerLocation, driver->getLocation())
                        << "the driver hasnt reached the passenger" << endl;
   // delete (driversRoute);
   // delete (passengerLocation);
   // delete (destination);
    delete (bfs);
    delete(passenger);
}
//.
TEST_F(TaxiStationTest, answerCallTest2) {
    NodeBlock *passengerLocation = map1->getBlock(Point(0,0));
    NodeBlock *destination = map1->getBlock(Point(5,5));
    BreadthFirstSearch *bfs = new BreadthFirstSearch(map1);
    Passenger *passenger = new Passenger(Point(0,0), Point(5,5));
    //gets the correct route that the bfs generates
    stack<Node *> correctRoute = bfs->breadthFirstSearch(passengerLocation, destination);
    taxiStation->answerCall(Point(5,5), passenger);
/*checks if the correct driver drove to the passenger
     * this test is different since we have now two drivers*/
    Driver *closeDriver = new Driver(20599, 25, 15, "single");
    closeDriver->setLocation(map1->getBlock(Point(0, 1)));
    taxiStation->addDriver(closeDriver);
    EXPECT_EQ(passengerLocation, closeDriver->getLocation())
                        << "the incorrect driver has been assigned" << endl;
    //checks if the closeDriver received any trip info. if not we cant continue with the test
    ASSERT_FALSE(closeDriver->getTripInfo() == NULL) << "the close driver has no trip info" << endl;
    //checks if the closeDriver has the correct route
    EXPECT_TRUE(areStacksEqual(&correctRoute, closeDriver->getTripInfo()->getRoute()))
                        << "the correct driver has the wrong route" << endl;
    /*
    delete (passengerLocation);
    delete (destination);
    delete (bfs);*/
    delete (bfs);
    delete(passenger);
    delete (closeDriver);
}
