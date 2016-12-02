#include "gtest/gtest.h"
#include "NodeBlock.h"

using namespace std;

NodeBlock n00 (Point(0,0));
NodeBlock n01 (Point(0,1));
NodeBlock n10 (Point(1,0));
NodeBlock n11 (Point(1,1));

TEST(BooleanTester, setVisitedTest) {
    n00.setVisited(false);
    n01.setVisited(true);
    n10.setVisited(true);
    n11.setVisited(false);
    ASSERT_FALSE(n00.isVisited()) << "wrong boolean value returned";
    ASSERT_FALSE(n11.isVisited()) << "wrong boolean value returned";
    ASSERT_TRUE(n01.isVisited()) << "wrong boolean value returned";
    ASSERT_TRUE(n10.isVisited()) << "wrong boolean value returned";
}

TEST(GetterTest, GetFatherTest) {
    n11.setFather(&n01);
    n01.setFather(&n00);
    ASSERT_TRUE(n11.getFather() != NULL) << "father wasn't set as expected";
    ASSERT_TRUE(n01.getFather() != NULL) << "father wasn't set as expected";
    ASSERT_EQ(n11.getFather(),&n01) << "wrong father was set";
    ASSERT_EQ(n01.getFather(),&n00) << "wrong father was set";
}
TEST(SetterTest, GetChildrenTest) {
    NodeBlock n12 (Point(1,2));
    NodeBlock n21 (Point(2,1));
    n11.setLeft(&n01);
    n11.setUp(&n12);
    n11.setRight(&n21);
    n11.setDown(&n10);


}