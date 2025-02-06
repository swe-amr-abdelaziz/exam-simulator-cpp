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
        answer = formailzeAnswer(answer, caseSensitive);

        if (validAnswers.empty()) {
            return answer;
        } // No validation needed

        std::vector<std::string> formalizedAnswers = validAnswers;
        std::transform(formalizedAnswers.begin(), formalizedAnswers.end(),
                       formalizedAnswers.begin(), [caseSensitive](const std::string& answer) {
                           return Utils::formailzeAnswer(answer, caseSensitive);
                       });

        if (std::find(formalizedAnswers.begin(), formalizedAnswers.end(), answer) !=
            formalizedAnswers.end()) {
            return answer;
        } else {
            std::cout << "Invalid answer. Please choose from: " << printAnswersArray(validAnswers)
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
        trueAnswer = toLower(trueAnswer);
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

char Utils::convertIndexToChoiceChar(uint8_t index) {
    if (index > 25) {
        throw std::invalid_argument("Invalid index, must be between 0 and 25");
    }
    return static_cast<char>(static_cast<uint8_t>('A') + index);
}

uint8_t Utils::convertChoiceCharToIndex(char ch) {
    auto charCode = std::toupper(ch);
    if (!(charCode >= 'A' && charCode <= 'Z')) {
        throw std::invalid_argument(
            "Invalid choice character, must be between A and Z (case insensitive)");
    }
    int index = charCode - 'A';
    return static_cast<uint8_t>(index < 0 ? 0 : index);
}

std::string Utils::printAnswersArray(const std::vector<std::string>& validAnswers) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < validAnswers.size(); ++i) {
        oss << (i == 0 ? "" : ", ") << validAnswers[i];
    }
    oss << "]";
    return oss.str();
}

std::string Utils::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string Utils::trim(const std::string& str) {
    const std::string whitespaces = " \t\n\r\f\v";
    std::string result = str;
    result.erase(0, result.find_first_not_of(whitespaces));
    result.erase(result.find_last_not_of(whitespaces) + 1);
    return result;
}

std::string Utils::formailzeAnswer(const std::string& answer, const bool& caseSensitive) {
    std::string formalizedAnswer = trim(answer);
    if (!caseSensitive) {
        formalizedAnswer = toLower(formalizedAnswer);
    }
    return formalizedAnswer;
}
