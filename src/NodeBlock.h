
#ifndef ADPROG1_1_NODEBLOCK_H
#define ADPROG1_1_NODEBLOCK_H

#include "Node.h"
#include "Point.h"
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/access.hpp>


using namespace std;
using namespace boost::archive;

/**
 *
 */
class NodeBlock : public Node {
private:
    friend class boost::serialization::access;
    /**
     * serialization of the class
     * @param ar is the serializing object.
     * @param version is the version of serializing object.
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        //ar& boost::serialization::base_object<Node>(*this);
        ar& visited;
        ar& father;//need to check if i need to serialize node
        ar& distance;
        ar& point;//need to serialize point
        ar& obstacle;
    }

protected:
    std::vector<Node*> children;
    bool visited;
    Node* father;
    int distance;
    Point* point;
    bool obstacle;
public:
    /**
     * Constructor that receives a point and set it as the value of the node.
     * @param point
     */
    NodeBlock(Point point);

    /**
     * destructor
     */
    ~NodeBlock();

    NodeBlock();

    /**
     * tells if the node been visited while searching
     * @return true or false.
     */
    bool isVisited();

    /**
     *
     * @return if the block is an obstacle
     */
    bool isObstacle();

    /**
     * set ablock to an obstacle
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

    /**
     * overrides ==
     */
    bool operator==(const NodeBlock& nodeBlock)const;
};


#endif //ADPROG1_1_NODEBLOCK_H