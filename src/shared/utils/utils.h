#ifndef UTILS_H
#define UTILS_H

#include "../enums/enums.h"
#include <gtest/gtest.h>
#include <string>

class Utils {
public:
    static RunMode getAppRunMode(int argc, char* argv[]);
};

#endif // UTILS_H
