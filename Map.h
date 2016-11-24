//
// Created by yair on 22/11/16.
//

#ifndef ADPROG1_1_MAP_H
#define ADPROG1_1_MAP_H

#include "NodeBlock.h"
#include "Graph.h"
#include <vector>

using namespace std;
/**
 * a Grid that built in a form of dynamic matrix (vector of vector) which each cell contains
 * a pointer of a NodeBlock and each NodeBlock points to his matrix neighbors.
 */
class Map : public Graph {
private:
    int rows;
    int columns;
    vector<vector<NodeBlock*>> nodes;

    /**
     * a private method that connect each NodeBlock to its neighbors.
     */
    void setChildren();

public:
    /**
     * Deconstructor.
     */
    ~Map();

    /**
     * Constructor.
     * @param rows int variable that represent the number of rows of the grid
     * @param columns int variable that represent the number of columns of the grid
     */
    Map(int rows, int columns);

    /**
     * The method create the grid and fill with pointers of NodeBlock
     */
    void create() override ;

    /**
     *
     */
    void updateChildren();

    /**
     *
     * @param point
     */
    void setObstacle(Point point);

    /**
     *
     * @param point
     * @return
     */
    Node* getBlock(Point point);
};

#endif //ADPROG1_1_MAP_H
