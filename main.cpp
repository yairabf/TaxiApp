#include <iostream>
#include "Map.h"
#include "BreadthFirstSearch.h"

int main() {
    int rows, column, xStart, yStart, xGoal, yGoal;
    char temp;
    cin >> column;
    cin >> temp;
    cin >> rows;
    cin >> temp;
    cin >> xStart;
    cin >> temp;
    cin >> yStart;
    cin >> temp;
    cin >> xGoal;
    cin >>temp;
    cin >> yGoal ;
    Map map = Map(column,rows);
    BreadthFirstSearch bfs;
    Node* start = map.getBlock(Point(xStart,yStart));
    Node* goal = map.getBlock(Point(xGoal,yGoal));
    std::stack<Node*> fast = bfs.breadthFirstSearch(start, goal);
    while (!fast.empty()) {
        cout << "(" << fast.top()->getValue()->getX() <<","<< fast.top()->getValue()->getY()<< ")" << endl;
        fast.pop();
    }
    return 0;
}