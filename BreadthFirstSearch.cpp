//
// Created by yair on 20/11/16.
//

#include "BreadthFirstSearch.h"

using namespace std;

stack<Node*> BreadthFirstSearch::breadthFirstSearch(Node *start, Node *goal) {
    queue < Node* > route;
    start->setDistance(0);
    start->setVisited(true);
    route.push(start);
    while (!route.empty()) {
        Node *current = route.front();
        route.pop();

        /*if we got to the wanted goal*/
        if(current == goal) {

            /* we create the stuck that will hold the fastest route and
             * push all the node from the goal to the start point*/
            stack <Node*> fastestRoute;
            while (current != NULL) {
                fastestRoute.push(current);
                current = current->getFather();
            }
            return fastestRoute;
        }
        /*while we search each node we push every unvisited child he have to the queue and
         * update the child distance from the start point */
        for(int i=0;i< current->getChildren()->size(); i++) {
            Node* node = current->getChildren()->at(i);
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

BreadthFirstSearch::BreadthFirstSearch(Graph* graph1) {
graph = graph1;
}
