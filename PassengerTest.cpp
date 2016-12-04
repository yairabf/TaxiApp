
#include <gtest/gtest.h>
#include "Passenger.h"

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

TEST_F(PassengerTest, RandomScoreTest) {
    ASSERT_TRUE(passenger->randomScore()>=0 && passenger->randomScore() <= 5 ) << "wrong value";
}