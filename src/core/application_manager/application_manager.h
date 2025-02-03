#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "../../shared/enums/enums.h"
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
    RunMode _runMode;
    int _run();
    int _test();
    int _generateQuestions();
};

#endif // APPLICATION_MANAGER_H
