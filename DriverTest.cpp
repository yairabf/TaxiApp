

#include "gtest/gtest.h"
#include "Driver.h"

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

TEST_F(DriverTest, AgeTest) {
    ASSERT_TRUE(driver.getAge() > 17) << "Driver's age isn't valid";
    ASSERT_EQ(driver.getAge(), 26) << "The driver age wasn't construct well";
    driver.setAge(34);
    ASSERT_EQ(driver.getAge(), 34) << "The driver age wasn't set well";
}

TEST_F(DriverTest, IdTest) {
    ASSERT_TRUE(driver.getId() >= 0) << "id is negative";
    ASSERT_EQ(driver.getId(), 305263501) << "id wasn't construct well";
    driver.setId(111111111);
    ASSERT_EQ(driver.getId(), 111111111) << "id wasn't set well";
}

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

TEST_F(DriverTest, StatusTest) {
    ASSERT_EQ(driver.getStatus(), "married") << "status wasn't construct well";
    driver.setStatus("divorce");
    ASSERT_EQ(driver.getStatus(), "divorce") << "status wasn't set well";
}

TEST_F(DriverTest, AvgSatisfactionTest) {
    ASSERT_EQ(driver.getAvgSatisfaction(),0) << "Average satisfaction wasn't construct well";
    driver.setAvgSatisfaction(4.4);
    ASSERT_TRUE(driver.getAvgSatisfaction() - 4.4 < 0.00001 ) << "Average satisfaction wasn't set well";
}