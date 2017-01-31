//
// Created by hanani on 31/01/17.
//
#include <iostream>
#include <vector>

#ifndef ADPROG1_1_INPUTVALIDITYTESTS_H
#define ADPROG1_1_INPUTVALIDITYTESTS_H
using namespace std;
class InputValidityTests {
public:
    InputValidityTests();

    string trim(const string& str);

    vector<string> inputBraker(string input, string delimiter);

};


#endif //ADPROG1_1_INPUTVALIDITYTESTS_H
