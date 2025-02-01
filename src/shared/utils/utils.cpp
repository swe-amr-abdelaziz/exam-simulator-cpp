#include "utils.h"

RunMode Utils::getAppRunMode(int argc, char* argv[]) {
    if (argc > 1) {
        std::string mode = argv[1];
        if (mode.compare(RUN_MODES.find(RunMode::TEST)->second) == 0) {
            return RunMode::TEST;
        }
        if (mode.compare(RUN_MODES.find(RunMode::GENERATE_QUESTIONS)->second) == 0) {
            return RunMode::GENERATE_QUESTIONS;
        }
    }
    return RunMode::NORMAL;
}

