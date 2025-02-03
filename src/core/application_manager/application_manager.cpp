#include "application_manager.h"

ApplicationManager::ApplicationManager(RunMode runMode) : runMode(runMode) {}

ApplicationManager::~ApplicationManager() {}

int ApplicationManager::run() {
    switch (this->runMode) {
        case RunMode::NORMAL:
            return this->runApp();
        case RunMode::TEST:
            return this->runTests();
        case RunMode::GENERATE_QUESTIONS:
            return this->generateQuestions();
        default:
            std::cerr << "Unknown run mode!" << std::endl;
            return 1;
    }
}

int ApplicationManager::runApp() {
    return 0;
}

int ApplicationManager::runTests() {
    return RUN_ALL_TESTS();
}

int ApplicationManager::generateQuestions() {
    return 0;
}
