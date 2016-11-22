//
// Created by yair on 22/11/16.
//

#include "Map.h"

void Map::setObstacle(Point point) {

}

void Map::updateChildren() {

}

Map::Map(int rows, int columns) {
    nodes[columns][rows];
    create();
}

void Map::create() {
    int x = 0, y = 0;
    for (x; x <= columns; x++) {
        for (y; y <= rows; y++) {
            nodes[x].push_back(new NodeBlock(*new Point(x,y)));
        }
    }
    for (x; x <= columns; x++) {
        for (y; y <= rows; y++) {
            if(x - 1 >= 0)
                nodes[x][y]->setLeft(nodes[x - 1][y]);
            if(y + 1 < rows)
                nodes[x][y]->setUp(nodes[x][y + 1]);
            if(x + 1 < columns )
                nodes[x][y]->setRight(nodes[x + 1][y]);
            if(y - 1 >= 0)
                nodes[x][y]->setDown(nodes[x][y - 1]);
        }
    }
}

Node* Map::getBlock(Point point) {
    return nodes[point.getX()][point.getY()];
}
