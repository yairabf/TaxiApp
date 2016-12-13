
#include <gtest/gtest.h>
#include "../src/Passenger.h"

/**
 * the class test passenger's functions
 */
using namespace std;
class PassengerTest: public ::testing::Test {
public:
    Passenger *passenger;
protected:
    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<< endl;
        passenger = new Passenger(Point(5,5), Point(0,0));
    }

    virtual void TearDown () {
        cout<<"tearing down" << endl;
        delete(passenger);
    }

public:
    PassengerTest(){};
};

/**
 * test if the method that charge of score the driver works.
 * we check if the method return a random number between 1 to 5.
 */
TEST_F(PassengerTest, RandomScoreTest) {
    ASSERT_TRUE(passenger->randomScore()>=0 && passenger->randomScore() <= 5 ) << "wrong value";
}