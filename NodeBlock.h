//
// Created by yair on 22/11/16.
//

#ifndef ADPROG1_1_NODEBLOCK_H
#define ADPROG1_1_NODEBLOCK_H

#include "Node.h"
#include "Point.h"

class NodeBlock : public Node {
private:
    Point point;
public:
    void setLeft(Node* left);

    void setRight(Node* right);

    void setUp(Node* up);

    void setDown(Node* down);

    NodeBlock(Point point);

    bool isVisited() override ;

    void setVisited(bool visited) override;

    std::vector<Node *> getChildren() override;

    Node *getFather() override;

    void setFather(Node *father) override;

    int getDistance() override;

    void setDistance(int d) override;

    Point* getValue() override ;

};
#endif //ADPROG1_1_NODEBLOCK_H
