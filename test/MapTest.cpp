#include "gtest/gtest.h"
#include "../src/Map.h"

using namespace std;

class MapTest: public ::testing::Test{
protected:
    Map map;
    virtual void SetUp() {
        cout << "Setting Up" << endl;
    }

    virtual void TearDown(){
        cout << "Tearing Down" << endl;
    }

public:
    MapTest():map(10,10){};
};

/**
 * the tests check if the creation of the maps works well.
 * first we runs through all the cells of the maps and check that they ar't null
 * then we check in each cell that it hold the correct value.
 */
TEST_F(MapTest, CreatTest) {
    for(int i = 0; i < 10; i++) {
        for (int j=0; j< 10; j++) {
            EXPECT_TRUE(map.getBlock(Point(i,j)) != NULL);
            Point ij (i,j);
            EXPECT_EQ(ij.toString(), map.getBlock(ij)->printValue())
                                << "uncorrected value of initialized block";
        }
    }
}

/**
 * the test check a private method that charge of setting each node it's neighbors
 * the method runs through all the cells and checks they points to their correct neighbors.
 */
TEST_F(MapTest, Neighbors) {
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for(int k = 0; k< map.getBlock(Point(i,j))->getChildren()->size(); k++) {
                if(i - 1 >= 0)
                    EXPECT_TRUE(map.getBlock(Point(i,j))->getChildren()->at(k) =
                                        map.getBlock(Point(i - 1, j)))<< "neighbor isn't correct";
                else if(j + 1 < 10)
                    EXPECT_TRUE(map.getBlock(Point(i, j))->getChildren()->at(k) =
                                        map.getBlock(Point(i, j + 1)))<< "neighbor isn't correct";
                else if(i + 1 > 10)
                    EXPECT_TRUE(map.getBlock(Point(i, j))->getChildren()->at(k) =
                                        map.getBlock(Point(i + 1, j)))<< "neighbor isn't correct";
                else if(j - 1 >= 0)
                    EXPECT_TRUE(map.getBlock(Point(i, j))->getChildren()->at(k) =
                                        map.getBlock(Point(i, j - 1)))<< "neighbor isn't correct";
            }
        }
    }
}

/**
 * the test make sure the the method the charge of reset all the nodes to be unvisited works well
 */
TEST_F(MapTest, UpdateChildrenTest) {
    for(int i = 0; i < 10; i++) {
        for (int j=0; j< 10; j++) {
            map.getBlock(Point(i, j))->setVisited(true);
        }
    }
    map.updateChildren();
    for(int i = 0; i < 10; i++) {
        for (int j=0; j< 10; j++) {
            EXPECT_FALSE(map.getBlock(Point(i, j))->isVisited()) << "The block" << map.getBlock(Point(i, j))
                                                                 << "wasn't updated";
        }
    }
}

/**
 * the test checks if the method set obstacle that set a specific node to be
 * an fit to been drove on, works.
 */
TEST_F(MapTest, ObstacleTest) {
	 /*creates and set all the nodes we want to set as obstacles*/
    Point p45(4,5);
    Point p12(1,2);
    Point p75(7,5);
    Point p13(1,3);
    Point p36(3,6);
    Point p49(4,9);
    map.setObstacle(p45);
    map.setObstacle(p12);
    map.setObstacle(p75);
    map.setObstacle(p13);
    map.setObstacle(p36);
    map.setObstacle(p49);
    EXPECT_TRUE(map.getBlock(p45)->getIsObstacle()) << "Obstacle wasn't set";
    EXPECT_TRUE(map.getBlock(p12)->getIsObstacle()) << "Obstacle wasn't set";
    EXPECT_TRUE(map.getBlock(p75)->getIsObstacle()) << "Obstacle wasn't set";
    EXPECT_TRUE(map.getBlock(p13)->getIsObstacle()) << "Obstacle wasn't set";
    EXPECT_TRUE(map.getBlock(p36)->getIsObstacle()) << "Obstacle wasn't set";
    EXPECT_TRUE(map.getBlock(p49)->getIsObstacle()) << "Obstacle wasn't set";
}
