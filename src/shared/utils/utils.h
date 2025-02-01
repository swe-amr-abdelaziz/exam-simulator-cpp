#ifndef UTILS_H
#define UTILS_H

#include "../enums/enums.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Utils {
public:
    static RunMode getAppRunMode(int argc, char* argv[]);
private:
    static std::string _printAnswersArray(const std::vector<std::string>& validAnswers);
};

#endif // UTILS_H
