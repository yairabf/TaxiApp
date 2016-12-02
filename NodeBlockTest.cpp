#include "gtest/gtest.h"
#include "NodeBlock.h"

using namespace std;

class NodeBlockTEst: public ::testing::Test{
    virtual void SetUp() {
        cout << "Setting Up" << endl;
    }

};

NodeBlock n00 (Point(0,0));
NodeBlock n01 (Point(0,1));
NodeBlock n10 (Point(1,0));
NodeBlock n11 (Point(1,1));


TEST(NodeBlockTest, VisitedTest) {
    n00.setVisited(false);
    n01.setVisited(true);
    n10.setVisited(true);
    n11.setVisited(false);
    ASSERT_FALSE(n00.isVisited()) << "wrong boolean value returned";
    ASSERT_FALSE(n11.isVisited()) << "wrong boolean value returned";
    ASSERT_TRUE(n01.isVisited()) << "wrong boolean value returned";
    ASSERT_TRUE(n10.isVisited()) << "wrong boolean value returned";
}

TEST(NodeBlockTest, FatherTest) {
    n11.setFather(&n01);
    n01.setFather(&n00);
    ASSERT_TRUE(n11.getFather() != NULL) << "father wasn't set as expected";
    ASSERT_TRUE(n01.getFather() != NULL) << "father wasn't set as expected";
    ASSERT_EQ(n11.getFather(),&n01) << "wrong father was set";
    ASSERT_EQ(n01.getFather(),&n00) << "wrong father was set";
}

TEST(NodeBlockTest, ChildrenTest) {
    NodeBlock n12 (Point(1,2));
    NodeBlock n21 (Point(2,1));
    n11.setLeft(&n01);
    n11.setUp(&n12);
    n11.setRight(&n21);
    n11.setDown(&n10);
    ASSERT_TRUE(n11.getChildren()->size()==4);
    EXPECT_TRUE(n11.getChildren()->at(0) != NULL) << "Children wasn't set as expected";
    EXPECT_TRUE(n11.getChildren()->at(0) = &n01) << "Wrong children was set";
    EXPECT_TRUE(n11.getChildren()->at(1) != NULL) << "Children wasn't set as expected";
    EXPECT_TRUE(n11.getChildren()->at(1) = &n12) << "Wrong children was set";
    EXPECT_TRUE(n11.getChildren()->at(2) != NULL) << "Children wasn't set as expected";
    EXPECT_TRUE(n11.getChildren()->at(2) = &n21) << "Wrong children was set";
    EXPECT_TRUE(n11.getChildren()->at(3) != NULL) << "Children wasn't set as expected";
    EXPECT_TRUE(n11.getChildren()->at(3) = &n10) << "Wrong children was set";
}

TEST(NodeBlockTest, DistancTest) {
    n00.setDistance(3);
    ASSERT_EQ(3, n00.getDistance()) << "Wrong value returned";
    n10.setDistance(5);
    ASSERT_EQ(5, n10.getDistance()) << "Wrong value returned";
    n00.setDistance(0);
    n10.setDistance(0);
    n01.setDistance(0);
    n11.setDistance(0);
    n11.setFather(&n01);
    n01.setFather(&n00);
    Node *node = &n11;
    while(node->getFather() != NULL) {
        node->getFather()->setDistance(node->getDistance() + 1);
        node = node->getFather();
    }
    ASSERT_EQ(n11.getDistance(),0) << "wrong distance";
    ASSERT_EQ(n01.getDistance(),1) << "wrong distance";
    ASSERT_EQ(n00.getDistance(),2) << "wrong distance";

}

