
#ifndef ADPROG1_1_BREADTHFIRSTSEARCH_H
#define ADPROG1_1_BREADTHFIRSTSEARCH_H

#include <stack>
#include <queue>
#include "Node.h"
#include "Graph.h"

/**
 * the class implement the BFS algorithm the class has a function that returns stuck full
 * of pointers to Node which are the fastest route from to points.
 */
class BreadthFirstSearch {
private:
    Graph* graph;
public:

    /**
 * the function calculate the fastest rout from one point to another.
 * the function use the BFS algorithm using a queue that help to make sure
 * that we breadth searching
 *
 * @param start a pointer to to node that represent the start point.
 * @param goal a pointer to to node that represent the goal point.
 * @return stuck full of pointers to node that represent the fastest route.
 */
    std::stack<Node*> breadthFirstSearch(Node* start, Node* goal);

    BreadthFirstSearch(Graph* graph);

    ~BreadthFirstSearch();
};

#endif //ADPROG1_1_BREADTHFIRSTSEARCH_H
