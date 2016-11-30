#include <iostream>
#include "Map.h"
#include "BreadthFirstSearch.h"

/**
 * The main method that runs the program, the method receives form the user the size of the grid
 * and the location of the start point and the goal and the method prints the the fastest route.
 * @return hanay
 */
int main() {
    int rows, column, xStart, yStart, xGoal, yGoal;
    char temp;

    /* reading from the user the value */
    cin >> column;
    cin >> temp;
    cin >> rows;
    cin >> temp;
    cin >> xStart;
    cin >> temp;
    cin >> yStart;
    cin >> temp;
    cin >> xGoal;
    cin >> temp;
    cin >> yGoal;

    // creating the map
    Map map = Map(column, rows);
    BreadthFirstSearch bfs = BreadthFirstSearch(&map);

    //gets the pointers for the starting node and goal node
    Node *start = map.getBlock(Point(xStart, yStart));
    Node *goal = map.getBlock(Point(xGoal, yGoal));

    //receiving the fastest route using the BFS algorithm.
    std::stack<Node *> fast = bfs.breadthFirstSearch(start, goal);

    /*print the route*/
    while (!fast.empty()) {
        cout << *fast.top() << endl;
        fast.pop();
    }
    return 0;
}