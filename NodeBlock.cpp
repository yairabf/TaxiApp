//
// Created by yair on 22/11/16.
//

#include "NodeBlock.h"

void NodeBlock::setVisited(bool visited) {
    NodeBlock::visited = visited;
}

std::vector<Node *> NodeBlock::getChildren() {
    children;
}

Node *NodeBlock::getFather() {
    father;
}

void NodeBlock::setFather(Node *father) {
    NodeBlock::father = father;
}

int NodeBlock::getDistance() {
    return distance;
}

void NodeBlock::setDistance(int d) {
    NodeBlock::distance = d;
}

bool NodeBlock::isVisited() {
    return visited;
}

NodeBlock::NodeBlock(Point point) : point(point) {}

void NodeBlock::setLeft(Node *left) {
    children[0] = left;
}

void NodeBlock::setRight(Node *right) {
    children[2] = right;
}

void NodeBlock::setUp(Node *up) {
    children[1] = up;
}

void NodeBlock::setDown(Node *down) {
    children[3] = down;
}

void *NodeBlock::getValue() {
    return &point;
}
