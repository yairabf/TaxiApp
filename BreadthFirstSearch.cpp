//
// Created by yair on 20/11/16.
//

#include "BreadthFirstSearch.h"

using namespace std;

stack<Node*> BreadthFirstSearch::breadthFirstSearch(Node *start, Node *goal) {
    queue<Node*> route;
    start->setDistance(0);
    start->setVisited(true);
    route.push(start);
    while (!route.empty()) {
        Node *current = route.front();
        route.pop();
        if(current == goal) {
            stack<Node*> fastestRoute;
            while (current != nullptr) {
                fastestRoute.push(current);
                current = current->getFather();
            }
            return fastestRoute;
        }
        for(Node* node : *current->getChildren()) {
            if(!node->isVisited()) {
                node->setDistance(current->getDistance() + 1);
                node->setVisited(true);
                node->setFather(current);
                route.push(node);
            }
        }
    }
    stack <Node*> empty;
    return empty;
}
