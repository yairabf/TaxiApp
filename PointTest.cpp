#include "gtest/gtest.h"
#include "Point.h"
//here doesnt work
using namespace std;

class PointTest: public ::testing::Test{
protected:
    Point* p1;
    Point* p2;
    Point* p3;
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

public:
    PointTest(){};
};

TEST_F(PointTest, GetXPointTest){
    ASSERT_EQ(p1->getX(),1) << "Getter return wrong value";
    ASSERT_EQ(p2->getX(),2) << "Getter return wrong value";
    ASSERT_EQ(p1->getX(),p3->getX()) << "Getter return wrong value";
    EXPECT_GT(p2->getX(),p1->getX()) << "Getter return wrong value";
}

TEST_F(PointTest, GetYPointTest){
    ASSERT_EQ(p1->getY(),1) << "Getter return wrong value";
    ASSERT_EQ(p2->getY(),2) << "Getter return wrong value";
    ASSERT_EQ(p1->getY(),p3->getY()) << "Getter return wrong value";
    EXPECT_GT(p2->getY(),p1->getY()) << "Getter return wrong value";
}

TEST_F(PointTest, overrideFunctionTest) {
    ASSERT_TRUE(*p1 == *p3)<<"the override didnt work"<<endl;
}



