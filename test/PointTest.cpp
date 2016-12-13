#include "gtest/gtest.h"
#include "../src/Point.h"

using namespace std;

/**
 * class that checks the point class.
 */
class PointTest: public ::testing::Test{
public:
    Point *p1;
    Point *p2;
    Point *p3;
protected:
    virtual void SetUp() {
        cout << "Setting Up" << endl;
        p1 = new Point(1,1);
        p2 = new Point(2,2);
        p3 = new Point(1,1);
    }

    virtual void TearDown(){
        cout << "Tearing Down" << endl;
        delete(p1);
        delete(p2);
        delete(p3);
    }
};

/**
 * test for the getter
 */
TEST_F(PointTest, GetXPointTest){
    ASSERT_EQ(p1->getX(),1) << "Getter return wrong value";
    ASSERT_EQ(p2->getX(),2) << "Getter return wrong value";
    ASSERT_EQ(p1->getX(),p3->getX()) << "Getter return wrong value";
    EXPECT_GT(p2->getX(),p1->getX()) << "Getter return wrong value";
}

/**
 * test for the getter
 */
TEST_F(PointTest, GetYPointTest){
    ASSERT_EQ(p1->getY(),1) << "Getter return wrong value";
    ASSERT_EQ(p2->getY(),2) << "Getter return wrong value";
    ASSERT_EQ(p1->getY(),p3->getY()) << "Getter return wrong value";
    EXPECT_GT(p2->getY(),p1->getY()) << "Getter return wrong value";
}

/**
 * test if the overloading operator works.
 */
TEST_F(PointTest, overrideFunctionTest) {
    ASSERT_TRUE(*p1 == *p3)<<"the override didnt work"<<endl;
}



