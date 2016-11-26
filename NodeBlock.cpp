//
// Created by yair on 22/11/16.
//

#include "NodeBlock.h"
#include <sstream>
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

string NodeBlock::printValue() {
    string x = static_cast<ostringstream*>( &(ostringstream() << point.getX()) )->str();
    string y = static_cast<ostringstream*>( &(ostringstream() << point.getY()) )->str();
    return   "("  + x + ", " + y + ")";
}

//

std::ostream& operator<<(std::ostream& out, Node& node) {
    out << node.printValue();
    return out;
};

