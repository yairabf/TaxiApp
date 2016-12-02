
#ifndef ADPROG1_1_NODE_H
#define ADPROG1_1_NODE_H

#include <vector>
#include "Point.h"
#include <string>

/**
 * An abstract class that represent Node/Vertex of a graph the node
 * has functionality that let use him for calculating route print the
 * value it holds. etc..
 */
class Node {
protected:
    std::vector<Node*> children;
    bool visited;
    Node* father;
    int distance;

public:
    /**
     * a setter for the boolean variable that tells us if the node been visited while searching
     * @param visited the boolean variable.
     */
    virtual void setVisited(bool visited) = 0;

    /**
     * getter for the children/neighbors of the node.
     * @return vector with neighbors
     */
    virtual std::vector<Node*>* getChildren() = 0;
    /**
     * getter for a specific father that determent while searching a route.
     * @return the node's father.
     */
    virtual Node* getFather() = 0;

    /**
     * setter for the father.
     * @param father
     */
    virtual void setFather(Node* father) = 0;

    /**
     * getter for the distance of the node from the start point while searching.
     * @return the distance from the start point.
     */
    virtual int getDistance() = 0;

    /**
     * setter for the distance
     * @param d the distance from the start point
     */
    virtual void setDistance(int d) = 0;

    /**
     * setter for the boolean value that tells us if the node been visited
     * @param visited true or false.
     */
    virtual bool isVisited() = 0;

    /**
     * prints the vaule that the node holds.
     */
    virtual std::string printValue() = 0;

};

/**
 * overloading for the out stream.
 * @param out output of the values that the Ndoe holds
 * @param node the node that we want to output his vlaue
 * @return
 */
std::ostream&operator<<(std::ostream& out, Node& node);


#endif //ADPROG1_1_NODE_H
