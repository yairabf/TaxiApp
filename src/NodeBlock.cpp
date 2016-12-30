
#include "NodeBlock.h"
#include <sstream>
#include <boost/serialization/export.hpp>

using namespace std;



NodeBlock::NodeBlock(Point point) : point(point) {
    distance = 0;
    father = NULL;
    visited = false;
}

NodeBlock::~NodeBlock() {
}

void NodeBlock::setLeft(Node *left) {
    children.push_back(left);
}

void NodeBlock::setRight(Node *right) {
    children.push_back(right);
}

void NodeBlock::setUp(Node *up) {
    children.push_back(up);
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

bool NodeBlock::isObstacle() {
    return obstacle;
}

void NodeBlock::setIsObstacle(bool isObstacle) {
    NodeBlock::obstacle = isObstacle;
}

using namespace std;
using namespace boost::archive;

template<class Archive>
void NodeBlock::serialize(Archive & ar, const unsigned int version) {
    ar& boost::serialization::base_object<Node>(*this);
    ar& visited;
    ar& father;//need to check if i need to serialize node
    ar& distance;
    ar& point;//need to serialize point
    ar& obstacle;
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

/**
 * overloading the operator "==" of an out stream.
 * @param out
 * @param node
 * @return
 */
bool NodeBlock::operator==(const NodeBlock& nodeBlock)const{
    return(point == nodeBlock.point);
};
BOOST_CLASS_EXPORT(NodeBlock);
