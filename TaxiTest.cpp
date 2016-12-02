//
// Created by hanani on 02/12/16.
//
#include <gtest/gtest.h>
#include "Taxi.h"
//changed here
using namespace std;
class TaxiTest: public ::testing::Test {
protected:
    Taxi static *taxi;
    virtual void SetUp() {
        cout<<"setting up for TaxiTest"<<endl;
        Taxi taxi(203990924, 120, "Fiat", "Black", 2, 5.00);
    }
    TEST(GettersTests, GetIdTest) {
        ASSERT_EQ(taxi->getId(), 203990924)<<"didnt manage to update id";
    }
    TEST(GettersTests, GetNumOfKmPassedTest) {
        ASSERT_EQ(taxi->getNumOfKmPassed(), 120)<<"didnt manage to update id numOfKm";
    }
    TEST(GettersTests, GetCarManufacturerTest) {
        ASSERT_EQ(taxi->getCarManufacturer(), "Fiat")<<"didnt manage to update car manufacturer";
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

    virtual void TearDown () {
        cout<<"tearing down"<<endl;
        delete(taxi);
    }
};

