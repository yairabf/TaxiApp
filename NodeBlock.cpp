//
// Created by yair on 22/11/16.
//

#include "NodeBlock.h"



NodeBlock::NodeBlock(Point point) : point(point) {}

void NodeBlock::setLeft(Node *left) {
    children.resize(children.size() + 1);
    children.push_back(left);
}

void NodeBlock::setRight(Node *right) {
    children.resize(children.size() + 1);
    children .push_back(right);
}

void NodeBlock::setUp(Node *up) {
    children.resize(children.size() + 1);
    children .push_back(up);
}

void NodeBlock::setDown(Node *down) {
    children.resize(children.size() + 1);
    children.push_back(down);
}

void *NodeBlock::getValue() {
    return NodeBlock::point;
};


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
