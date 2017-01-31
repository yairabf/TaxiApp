//
// Created by hanani on 31/01/17.
//

#include "InputValidityTests.h"
InputValidityTests::InputValidityTests(){}

string InputValidityTests::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> InputValidityTests::inputBraker(string input, string delimiter) {
    vector<string> vector;
    size_t pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        if(token != "") {
            //deleting whitespaces
            token = trim(token);
            vector.push_back(token);
        }
        input.erase(0, pos + delimiter.length());
    }
    vector.push_back(input);
    return vector;
}