#include "gtest/gtest.h"
#include "Point.h"
//here doesnt work
using namespace std;
Point p1(1,1);
Point p2(2,2);

TEST(GetterTest, GetXPointTest){
    Point p3(1,1);
    ASSERT_EQ(p1.getX(),1) << "Getter return wrong value";
    ASSERT_EQ(p2.getX(),2) << "Getter return wrong value";
    ASSERT_EQ(p1.getX(),p3.getX()) << "Getter return wrong value";
    EXPECT_GT(p2.getX(),p1.getX()) << "Getter return wrong value";
}

TEST(GetterTest, GetYPointTest){
    Point p3(1,1);
    ASSERT_EQ(p1.getY(),1) << "Getter return wrong value";
    ASSERT_EQ(p2.getY(),2) << "Getter return wrong value";
    ASSERT_EQ(p1.getY(),p3.getY()) << "Getter return wrong value";
    EXPECT_GT(p2.getY(),p1.getY()) << "Getter return wrong value";
}

