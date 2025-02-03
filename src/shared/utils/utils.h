#ifndef UTILS_H
#define UTILS_H

#include "../enums/enums.h"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Utils {
public:
    static RunMode getAppRunMode(const int& argc, char* argv[]);
    static std::string askQuestion(const std::string& question,
                                   const std::vector<std::string>& validAnswers = {},
                                   bool caseSensitive = false);
    static std::vector<std::string> split(std::string str, char delimiter = '\n');

private:
    static std::string _printAnswersArray(const std::vector<std::string>& validAnswers);
    static std::string _toLower(const std::string& str);
    static std::string _trim(const std::string& str);
    static std::string _formailzeAnswer(const std::string& answer, const bool& caseSensitive);
};

#endif // UTILS_H
