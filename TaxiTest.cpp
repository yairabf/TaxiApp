
#include <gtest/gtest.h>
#include "Taxi.h"

using namespace std;
class TaxiTest: public ::testing::Test {
public:
    Taxi *taxi;
protected:
    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<< endl;
        taxi = new Taxi(203990924, 120, "Fiat", "Black", 2, 5.00);
    }

    virtual void TearDown () {
        cout<<"tearing down" << endl;
        delete(taxi);
    }

public:
    TaxiTest(){};
};

TEST_F(TaxiTest, GetIdTest) {
    ASSERT_EQ(taxi->getId(), 203990924)<<"didn't manage to update id";
}
TEST_F(TaxiTest, GetNumOfKmPassedTest) {
    ASSERT_EQ(taxi->getNumOfKmPassed(), 120)<<"didn't manage to update id numOfKm";
}
TEST_F(TaxiTest, GetCarManufacturerTest) {
    ASSERT_EQ(taxi->getCarManufacturer(), "Fiat")<<"didn't manage to update car manufacturer";
}
TEST_F(TaxiTest, GetCarColorTest) {
    ASSERT_EQ(taxi->getColor(), "Black")<<"didn't manage to update color";
}
TEST_F(TaxiTest, GetSpeedTest) {
    ASSERT_EQ(taxi->getSpeed(), 2)<<"didn't manage to update speed";
}
TEST_F(TaxiTest, GetTariffTest) {
    ASSERT_EQ(taxi->getTariff(), 5.00)<<"didn't manage to update tariff";
}
TEST_F(TaxiTest, CalculatePriceTest) {
    ASSERT_EQ(taxi->calculatePrice(10), 50) << "didn't calculate correctly";
    ASSERT_ANY_THROW(taxi->calculatePrice(-10)) << "Km value isn't valid";

}