#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "../../shared/constants/enums.h"
#include "../../shared/utils/utils.h"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

class ApplicationManager {
public:
    ApplicationManager(RunMode runMode);
    ~ApplicationManager();
    int run();

private:
    RunMode runMode;
    int runApp();
    int runTests();
    int generateQuestions();
};

#endif // APPLICATION_MANAGER_H
