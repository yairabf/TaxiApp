
#include <gtest/gtest.h>
#include "../src/Taxi.h"

using namespace std;
class TaxiTest: public ::testing::Test {
public:
    Taxi *taxi;
protected:
    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<< endl;
        taxi = new Taxi(1111,'F','B',2);
    }

    virtual void TearDown () {
        cout<<"tearing down" << endl;
        delete(taxi);
    }

public:
    TaxiTest(){};
};

TEST_F(TaxiTest, GetIdTest) {
    ASSERT_EQ(taxi->getId(), 1111)<<"didn't manage to update id";
}
TEST_F(TaxiTest, GetSpeedTest) {
    ASSERT_EQ(taxi->getSpeed(), 2)<<"didn't manage to update speed";
}
TEST_F(TaxiTest, CalculatePriceTest) {
    taxi->setTripInfo(new TripInfo(0,0,0,5,5,2,2.0));
    ASSERT_EQ(taxi->calculatePrice(8), 16) << "didn't calculate correctly";
    ASSERT_ANY_THROW(taxi->calculatePrice(-10)) << "Km value isn't valid";
    delete(taxi->getTripInfo());

}