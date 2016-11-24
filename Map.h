//
// Created by yair on 22/11/16.
//

#ifndef ADPROG1_1_MAP_H
#define ADPROG1_1_MAP_H

#include "NodeBlock.h"
#include <vector>

using namespace std;
/**
 *
 */
class Map {
private:
    int rows;
    int columns;
    vector<vector<NodeBlock*>> nodes;

public:
    ~Map();
    Map(int rows, int columns);
    void create();
    void updateChildren();
    void setObstacle(Point point);
    Node* getBlock(Point point);
};

#endif //ADPROG1_1_MAP_H
