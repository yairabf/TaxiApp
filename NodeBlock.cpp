//
// Created by yair on 22/11/16.
//

#include "NodeBlock.h"
using namespace std;



NodeBlock::NodeBlock(Point point) : point(point) {}

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

string NodeBlock::printValue() const {
    return   "("  + to_string(point.getX()) + ", " + to_string(point.getY()) + ")5_5,0_0,2_2";
}

//

std::ostream& operator<<(std::ostream& out, const Node& node) {
    out << node.printValue();
    return out;
};

