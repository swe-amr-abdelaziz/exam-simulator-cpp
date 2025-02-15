#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <constants/enums.h>

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
