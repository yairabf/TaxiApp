
#include "NodeBlock.h"
#include <sstream>
using namespace std;



NodeBlock::NodeBlock(Point point) : point(point) {
    distance = 0;
    father = NULL;
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

void NodeBlock::setVisited(bool visited) {
    NodeBlock::visited = visited;
}

std::vector<Node *>* NodeBlock::getChildren() {
    return &children;
}

Node* NodeBlock::getFather() {
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
    return point.toString();
}

bool NodeBlock::getIsObstacle() {
    return isObstacle;
}

void NodeBlock::setIsObstacle(bool isObstacle) {
    NodeBlock::isObstacle = isObstacle;
}

/**
 * overloading the operator "<<" of an out stream.
 * @param out
 * @param node
 * @return
 */
std::ostream& operator<<(std::ostream& out, Node& node) {
    out << node.printValue();
    return out;
};

