#include <iostream>
#include "Map.h"
#include "BreadthFirstSearch.h"

int main() {
    Map map = Map(5,5);
    BreadthFirstSearch bfs;
    Node* start = map.getBlock(Point(0,0));
    Node* goal = map.getBlock(Point(4,4));
    std::stack<Node*> fast = bfs.breadthFirstSearch(start, goal);
    while (!fast.empty()) {
        cout << "(" << fast.top()->getValue()->getX() <<","<< fast.top()->getValue()->getY()<< ")" << endl;
        fast.pop();
    }
    return 0;
}