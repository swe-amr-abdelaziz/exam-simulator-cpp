#include "utils.h"

RunMode Utils::getAppRunMode(const int& argc, char* argv[]) {
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

std::string Utils::askQuestion(const std::string& question,
                               const std::vector<std::string>& validAnswers, bool caseSensitive) {
    while (true) {
        std::cout << question << '\n';
        std::string answer;
        std::getline(std::cin, answer);
        answer = _formailzeAnswer(answer, caseSensitive);

        if (validAnswers.empty()) {
            return answer;
        } // No validation needed

        std::vector<std::string> formalizedAnswers = validAnswers;
        std::transform(formalizedAnswers.begin(), formalizedAnswers.end(),
                       formalizedAnswers.begin(), [caseSensitive](const std::string& answer) {
                           return Utils::_formailzeAnswer(answer, caseSensitive);
                       });

        if (std::find(formalizedAnswers.begin(), formalizedAnswers.end(), answer) !=
            formalizedAnswers.end()) {
            return answer;
        } else {
            std::cout << "Invalid answer. Please choose from: " << _printAnswersArray(validAnswers)
                      << " (case " << (caseSensitive ? "sensitive" : "insensitive") << ")" << std::endl
                      << std::endl;
        }
    }
}

bool Utils::askBoolQuestion(const std::string& question,
                            const std::vector<std::string>& validAnswers, bool caseSensitive) {
    std::string answer = Utils::askQuestion(question, validAnswers, caseSensitive);
    auto trueAnswer = validAnswers[0];
    if (!caseSensitive) {
        trueAnswer = _toLower(trueAnswer);
    }
    return answer.compare(trueAnswer) == 0;
}

std::vector<std::string> Utils::split(std::string str, char delimiter) {
    std::istringstream buffer(str);
    std::string substr;
    std::vector<std::string> vec = {};
    while (getline(buffer, substr, delimiter))
        vec.push_back(substr.c_str());
    return vec;
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

std::string Utils::_trim(const std::string& str) {
    const std::string whitespaces = " \t\n\r\f\v";
    std::string result = str;
    result.erase(0, result.find_first_not_of(whitespaces));
    result.erase(result.find_last_not_of(whitespaces) + 1);
    return result;
}

std::string Utils::_formailzeAnswer(const std::string& answer, const bool& caseSensitive) {
    std::string formalizedAnswer = _trim(answer);
    if (!caseSensitive) {
        formalizedAnswer = _toLower(formalizedAnswer);
    }
    return formalizedAnswer;
}
