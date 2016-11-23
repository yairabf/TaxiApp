//
// Created by yair on 22/11/16.
//

#ifndef ADPROG1_1_NODE_H
#define ADPROG1_1_NODE_H

#include <vector>
#include "Point.h"

class Node {
protected:
    std::vector<Node*> children;
    bool visited;
    Node* father;
    int distance;

public:
    virtual bool isVisited() = 0;
    virtual void setVisited(bool visited) = 0;
    virtual std::vector<Node*> getChildren() = 0;
    virtual Node* getFather() = 0;
    virtual void setFather(Node* father) = 0;
    virtual int getDistance() = 0;
    virtual void setDistance(int d) = 0;
    virtual Point* getValue() = 0;
};

#endif //ADPROG1_1_NODE_H
