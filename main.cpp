#include <iostream>
#include "gtest/gtest.h"
#include "src/MainFlow.h"

/**
 * The main method that runs the program, the method receives form the user the size of the grid
 * and the location of the start point and the goal and the method prints the the fastest route.
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();
    int columns, rows;
    char temp;
    cout << "Please insert the size of the gird" << endl;
    cin >> columns;
    cin >> rows;
    MainFlow mainFlow = MainFlow(columns, rows);
    mainFlow.run();
    return 1;
}

