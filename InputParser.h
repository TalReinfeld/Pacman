#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class InputParser {
private:
    std::vector <std::string> tokens;
public:
    //ctor
    InputParser(int& argc, char** argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    const std::string& getCmdOption(const std::string& option) const;
    bool cmdOptionExists(const std::string& option) const;
    //void argForMain(int agrc, char** argv);
};

