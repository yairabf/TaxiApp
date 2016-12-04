
#include <gtest/gtest.h>
#include "Taxi.h"
<<<<<<< Updated upstream

using namespace std;
class TaxiTest: public ::testing::Test {
protected:
    Taxi taxi;

    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<<endl;
    }

    virtual void TearDown () {
        cout<<"tearing down"<<endl;
=======
using namespace std;
class TaxiTest: public ::testing::Test {
public:
    Taxi static *taxi;
protected:
    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<<endl;
        Taxi *taxi = new Taxi(203990924, 120, "Fiat", "Black", 2, 5.00);
    }

    virtual void TearDown () {
        //do nothing
>>>>>>> Stashed changes
    }

public:
    TaxiTest():taxi(203990924, 120, "Fiat", "Black", 2, 5.00){};
};

<<<<<<< Updated upstream
TEST_F(TaxiTest, GetIdTest) {
    ASSERT_EQ(taxi.getId(), 203990924)<<"didnt manage to update id";
}
TEST_F(TaxiTest, GetNumOfKmPassedTest) {
    ASSERT_EQ(taxi.getNumOfKmPassed(), 120)<<"didnt manage to update id numOfKm";
}
TEST_F(TaxiTest, GetCarManufacturerTest) {
    ASSERT_EQ(taxi.getCarManufacturer(), "Fiat")<<"didnt manage to update car manufacturer";
}
TEST_F(TaxiTest, GetCarColorTest) {
    ASSERT_EQ(taxi.getColor(), "Black")<<"didnt manage to update color";
}
TEST_F(TaxiTest, GetSpeedTest) {
    ASSERT_EQ(taxi.getSpeed(), 2)<<"didnt manage to update speed";
}
TEST_F(TaxiTest, GetTariffTest) {
    ASSERT_EQ(taxi.getTariff(), 5.00)<<"didnt manage to update tariff";
}


=======
TEST(GettersTests, GetIdTest) {
    ASSERT_EQ(taxi->getId(), 203990924)<<"didnt manage to update id";
}
TEST(GettersTests, GetNumOfKmPassedTest) {
    ASSERT_EQ(taxi->getNumOfKmPassed(), 120)<<"didnt manage to update id numOfKm";
}
TEST(GettersTests, GetCarManufacturerTest) {
    ASSERT_EQ(taxi->getCarManufacturer().size, 4)<<"string not equal length";
    EXPECT_EQ(taxi->getCarManufacturer(), "Fiat")<<"didnt manage to update car manufacturer";
}
TEST(GettersTest, GetCarColorTest) {
    ASSERT_EQ(taxi->getColor(), "Black")<<"didnt manage to update color";
}
TEST(GettersTest, GetSpeedTest) {
    ASSERT_EQ(taxi->getSpeed(), 2)<<"didnt manage to update speed";
}
TEST(GettersTest, GetTariffTest) {
    ASSERT_EQ(taxi->getTariff(), 5.00)<<"didnt manage to update tariff";
}

>>>>>>> Stashed changes
