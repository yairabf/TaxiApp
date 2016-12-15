#include "gtest/gtest.h"
#include "../src/BreadthFirstSearch.h"
#include "../src/Map.h"

using namespace std;

/**
 * class that test the BreadthFirstSearch and checks if  all it functionality works.
 */
class BreadthFirstSearchTest: public ::testing::Test{
protected:
    virtual void SetUp() {
        map = new Map(10,10);
        cout << "Setting Up" << endl;
    }

    virtual void TearDown(){
        delete(map);
        cout << "Tearing Down" << endl;
    }

public:
    Map* map;
    BreadthFirstSearchTest(){}
};

/**
 * Test the BFS algorithm, the test creates 3 routs and the and then send to the BFS to
 * start and te end points of these three routes after the calculation, the test check if
 * the routes that been calculated by the BFS algorithm are identical to the three routes the
 * test create in the beginning.
 */
TEST_F(BreadthFirstSearchTest, FastestRouteTest) {
    /*creating the start and the end point of rhe first route*/
    Node* route1Start = map->getBlock(Point(0, 0));
    Node* route1End = map->getBlock(Point(9, 9));

    /*create a queue and insert it the actually route that supposed to been calculate */
    vector<Node *> fast1Test;

    for (int i = 0; i < 10; i++) {
        fast1Test.push_back(new NodeBlock(Point(0, i)));
    }
    for (int i = 1; i < 10; i++) {
        fast1Test.push_back(new NodeBlock(Point(i, 9)));
    }

    /*creating the start and the end point of the second route*/
    Node *route2Start = map->getBlock(Point(9, 9));
    Node *route2End = map->getBlock(Point(0, 0));

    /*create a queue and insert it the actually route that supposed to been calculate */
    vector<Node *> fast2Test;
    for (int i = 9; i >= 0; i--) {
        fast2Test.push_back(new NodeBlock(Point(i, 9)));
    }
    for (int i = 8; i >= 0; i--) {
        fast2Test.push_back(new NodeBlock(Point(0, i)));
    }

    /*creating the start and the end point of rhe second route*/
    Node *route3Start = map->getBlock(Point(9, 0));
    Node *route3End = map->getBlock(Point(0, 9));

    /*create a queue and insert it the actually route that supposed to been calculate */
    vector<Node *> fast3Test;
    for (int i = 9; i >= 0; i--) {
        fast3Test.push_back(new NodeBlock(Point(i, 0)));
    }
    for (int i = 1; i < 10; i++) {
        fast3Test.push_back(new NodeBlock(Point(0, i)));
    }

    /*calculate the fastest route and checks if it the correct one.*/
    BreadthFirstSearch bfs = BreadthFirstSearch(map);
    std::stack<Node *> fast1 = bfs.breadthFirstSearch(route1Start, route1End);
    int i= 0;
    /*compare the two routes*/
    while (!fast1.empty()) {
        EXPECT_EQ(fast1.top()->printValue(), fast1Test.at(i)->printValue());
        i++;
        fast1.pop();

    }
    map->resetVisited();
    /*calculate the fastest route and checks if it the correct one.*/
    std::stack<Node *> fast2 = bfs.breadthFirstSearch(route2Start, route2End);
    i = 0;
    /*compare the two routes*/
    while (!fast2.size()<0) {
        EXPECT_EQ(fast2.top()->printValue(), fast2Test.at(i)->printValue());
        fast2.pop();
        i++;
    }
    map->resetVisited();
    /*calculate the fastest route and checks if it the correct one.*/
    std::stack<Node *> fast3 = bfs.breadthFirstSearch(route3Start, route3End);
    i = 0;
    /*compare the two routes*/
    while (!fast3.size()<0) {
        EXPECT_EQ(fast3.top()->printValue(), fast3Test.at(i)->printValue());
        fast3.pop();
        i++;
    }

    /*handling the memory release*/
    for(int j = 0; j < fast1Test.size(); j++){
        delete(fast1Test.at((unsigned long) j));
        delete(fast2Test.at((unsigned long) j));
        delete(fast3Test.at((unsigned long) j));
    }
}