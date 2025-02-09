#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "../../shared/constants/enums.h"
#include "../../shared/constants/messages.h"
#include "../../shared/utils/utils.h"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

class ApplicationManager {
public:
    ApplicationManager(Enums::RunMode runMode);
    ~ApplicationManager();
    int run();

private:
    Enums::RunMode runMode;
    int runApp();
    int runTests();
    int generateQuestions();
};

#endif // APPLICATION_MANAGER_H
