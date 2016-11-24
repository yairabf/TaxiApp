//
// Created by yair on 22/11/16.
//

#include "NodeBlock.h"



NodeBlock::NodeBlock(Point point) : point(point) {}


NodeBlock::~NodeBlock() {

}

void NodeBlock::setLeft(Node *left) {
    children.push_back(left);
}

void NodeBlock::setRight(Node *right) {
    children .push_back(right);
}

void NodeBlock::setUp(Node *up) {
    children .push_back(up);
}

void NodeBlock::setDown(Node *down) {
    children.push_back(down);
}

Point* NodeBlock::getValue() {
    return &point;
};


void NodeBlock::setVisited(bool visited) {
    NodeBlock::visited = visited;
}

std::vector<Node *>* NodeBlock::getChildren() {
    return &children;
}

Node *NodeBlock::getFather() {
    return NodeBlock::father;
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
    return NodeBlock::visited;
}

