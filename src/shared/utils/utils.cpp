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

std::string Utils::_printAnswersArray(const std::vector<std::string>& validAnswers) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < validAnswers.size(); i++) {
        ss << (i == 0 ? "" : ", ") << validAnswers[i];
    }
    ss << "]";
    return ss.str();
}

std::string Utils::_toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
