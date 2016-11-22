//
// Created by yair on 20/11/16.
//

#include "BreadthFirstSearch.h"

using namespace std;

queue<Node*> BreadthFirstSearch::breadthFirstSearch(Node *start, Node *goal) {
    queue<Node*> route;
    start->setDistance(0);
    route.push(start);
    while (!route.empty()) {
        Node *current = route.front();
        route.pop();
        if(current == goal) {
            queue<Node*> fastestRoute;
            while (current != nullptr) {
                fastestRoute.push(current);
                current = current->getFather();
            }
            return fastestRoute;
        }
        current->setVisited(true);
        std::vector<Node*> children = current->getChildren();
        for(Node* node : children) {
            if(node!= nullptr && !node->isVisited()) {
                node->setDistance(current->getDistance() + 1);
                node->setFather(current);
                route.push(node);
            }
        }
    }
    queue <Node*> empty;
    return empty;
}
