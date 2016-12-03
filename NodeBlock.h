
#ifndef ADPROG1_1_NODEBLOCK_H
#define ADPROG1_1_NODEBLOCK_H

#include "Node.h"
#include "Point.h"
#include <string>


/**
 *
 */
class NodeBlock : public Node {
private:
    Point point;
    bool isObstacle = false;

public:
    /**
     * Constructor that receives a point and set it as the value of the node.
     * @param point
     */
    NodeBlock(Point point);

    /**
     * tells if the node been visited while searching
     * @return true or false.
     */
    bool isVisited();

    /**
     *
     * @return
     */
    bool getIsObstacle();

    /**
     *
     * @param isObstacle
     */
    void setIsObstacle(bool isObstacle);

    /**
     * setter for the boolean value that tells us if the node been visited
     * @param visited true or false.
     */
    void setVisited(bool visited);

    /**
     * getter that return pointer to tne vector of neighbors of the node.
     * @return pointer to the vector of nodes.
     */
    std::vector<Node *>* getChildren();

    /**
     * getter for the father of the node
     * @return pointer to the node's father.
     */
    Node *getFather();

    /**
     * setter for the node's father.
     * @param father
     */
    void setFather(Node *father);

    /**
     * getter for the distance of the node from the start point while searching.
     * @return the distance from the start point.
     */
    int getDistance();

    /**
     * setter for the distance
     * @param d the distance from the start point
     */
    void setDistance(int d);

    /**
     * set the left neighbor of the node
     * @param left neighbor.
     */
    void setLeft(Node* left);

    /**
     * set the right neighbor of the node
     * @param right neighbor
     */
    void setRight(Node* right);

    /**
     * set the upper neighbor of the node
     * @param up neighbor
     */
    void setUp(Node* up);

    /**
     * set the downer neighbor of the node
     * @param down neighbor
     */
    void setDown(Node* down);

    /**
     * prints the value that the node holds.
     */
    std::string printValue();
};
#endif //ADPROG1_1_NODEBLOCK_H
