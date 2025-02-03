#include "application_manager.h"

ApplicationManager::ApplicationManager(RunMode runMode) : _runMode(runMode) {}

ApplicationManager::~ApplicationManager() {}

int ApplicationManager::run() {
    switch (_runMode) {
        case RunMode::NORMAL:
            return _run();
        case RunMode::TEST:
            return _test();
        case RunMode::GENERATE_QUESTIONS:
            return _generateQuestions();
        default:
            std::cerr << "Unknown run mode!" << std::endl;
            return 1;
    }
}

int ApplicationManager::_run() {
    return 0;
}

int ApplicationManager::_test() {
    return RUN_ALL_TESTS();
}

int ApplicationManager::_generateQuestions() {
    return 0;
}
