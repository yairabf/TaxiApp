#include "gtest/gtest.h"
#include "BreadthFirstSearch.h"
#include "Map.h"

using namespace std;

class BreadthFirstSearchTest: public ::testing::Test{
protected:
    virtual void SetUp() {
        cout << "Setting Up" << endl;
    }

    virtual void TearDown(){
        cout << "Tearing Down" << endl;
    }

public:
    BreadthFirstSearchTest(){}
};

TEST_F(BreadthFirstSearchTest, FastestRouteTest) {
    Map map = Map(10,10);

    /*creating the start and the end point of rhe first route*/
    Node* route1Start = map.getBlock(Point(0, 0));
    Node* route1End = map.getBlock(Point(9, 9));

    /*create a queue and insert it the actually route that supposed to been calculate */
    vector<Node *> fast1Test;
    vector<Node*> memoryRelease;
    for (int i = 0; i < 10; i++) {
        fast1Test.push_back(new NodeBlock(Point(0, i)));
    }
    for (int i = 1; i < 10; i++) {
        fast1Test.push_back(new NodeBlock(Point(i, 9)));
    }

    /*creating the start and the end point of the second route*/
    Node *route2Start = map.getBlock(Point(9, 9));
    Node *route2End = map.getBlock(Point(0, 0));

    /*create a queue and insert it the actually route that supposed to been calculate */
    vector<Node *> fast2Test;
    for (int i = 9; i >= 0; i--) {
        fast2Test.push_back(new NodeBlock(Point(i, 9)));
    }
    for (int i = 8; i >= 0; i--) {
        fast2Test.push_back(new NodeBlock(Point(0, i)));
    }

    /*creating the start and the end point of rhe second route*/
    Node *route3Start = map.getBlock(Point(9, 0));
    Node *route3End = map.getBlock(Point(0, 9));

    /*create a queue and insert it the actually route that supposed to been calculate */
    vector<Node *> fast3Test;
    for (int i = 9; i >= 0; i--) {
        fast3Test.push_back(new NodeBlock(Point(i, 0)));
    }
    for (int i = 1; i < 10; i++) {
        fast3Test.push_back(new NodeBlock(Point(0, i)));
    }

    /*calculate the fastest route and checks if it the correct one.*/
    BreadthFirstSearch bfs = BreadthFirstSearch(&map);
    std::stack<Node *> fast1 = bfs.breadthFirstSearch(route1Start, route1End);
    int i= 0;
    while (!fast1.empty()) {
        EXPECT_EQ(fast1.top()->printValue(), fast1Test.at(i)->printValue());
        i++;
        fast1.pop();

    }

    /*calculate the fastest route and checks if it the correct one.*/
    std::stack<Node *> fast2 = bfs.breadthFirstSearch(route2Start, route2End);
    i = 0;
    while (!fast2.size()<0) {
        EXPECT_EQ(fast2.top()->printValue(), fast2Test.at(i)->printValue());
        fast2.pop();
        i++;
    }

    /*calculate the fastest route and checks if it the correct one.*/
    std::stack<Node *> fast3 = bfs.breadthFirstSearch(route3Start, route3End);
    i = 0;
    while (!fast3.size()<0) {
        EXPECT_EQ(fast3.top()->printValue(), fast3Test.at(i)->printValue());
        fast3.pop();
        i++;
    }
    int size = (int)memoryRelease.size();
    for(int i = 0; i<size; i++) {
        delete(memoryRelease.at((unsigned long) i));
    }
    for(int j = 0; j < fast1Test.size(); j++){
        delete(fast1Test.at(j));
        delete(fast2Test.at(j));
        delete(fast3Test.at(j));
    }
}