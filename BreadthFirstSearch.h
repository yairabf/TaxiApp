//
// Created by yair on 22/11/16.
//

#ifndef ADPROG1_1_BREADTHFIRSTSEARCH_H
#define ADPROG1_1_BREADTHFIRSTSEARCH_H

#include <queue>
#include "Node.h"

class BreadthFirstSearch {
public:
    std::queue<Node*> breadthFirstSearch(Node* start, Node* goal);
};

#endif //ADPROG1_1_BREADTHFIRSTSEARCH_H
