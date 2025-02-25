#include <algorithm>
#include <random>

#include <constants/enums.h>
#include <constants/messages.h>
#include <utils/utils.h>

Enums::RunMode Utils::getAppRunMode(const int& argc, char* argv[]) {
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

std::string Utils::askQuestion(const std::string& question, const std::vector<std::string>& validAnswers,
                               const bool& caseSensitive) {
    while (true) {
        std::cout << question << '\n';
        std::string answer;
        std::getline(std::cin, answer);
        answer = Utils::formailzeAnswer(answer, caseSensitive);

        if (validAnswers.empty()) {
            return answer;
        } // No validation needed

        std::vector<std::string> formalizedAnswers = validAnswers;
        std::transform(formalizedAnswers.begin(), formalizedAnswers.end(),
                       formalizedAnswers.begin(), [caseSensitive](const std::string& ans) {
                           return Utils::formailzeAnswer(ans, caseSensitive);
                       });

        if (std::find(formalizedAnswers.begin(), formalizedAnswers.end(), answer) !=
            formalizedAnswers.end()) {
            return answer;
        } else {
            std::cout << Messages::INVALID_MCQ_ANSWER << Utils::printAnswersArray(validAnswers)
                      << " (case " << (caseSensitive ? "sensitive" : "insensitive") << ")" << std::endl
                      << std::endl;
        }
    }
}

bool Utils::askBoolQuestion(const std::string& question,
                            const std::vector<std::string>& validAnswers, const bool& caseSensitive) {
    std::string answer = Utils::askQuestion(question, validAnswers, caseSensitive);
    auto trueAnswer = validAnswers[0];
    if (!caseSensitive) {
        trueAnswer = Utils::toLower(trueAnswer);
    }
    return answer.compare(trueAnswer) == 0;
}

std::vector<std::string> Utils::split(const std::string& str, const char& delimiter) {
    std::istringstream buffer(str);
    std::string substr;
    std::vector<std::string> vec = {};
    while (getline(buffer, substr, delimiter))
        vec.push_back(substr.c_str());
    return vec;
}

char Utils::convertIndexToChoiceChar(const uint8_t& index) {
    if (index > Utils::convertChoiceCharToIndex('Z')) {
        throw std::invalid_argument(Messages::INVALID_CHAR_INDEX);
    }
    return static_cast<char>(static_cast<uint8_t>('A') + index);
}

uint8_t Utils::convertChoiceCharToIndex(const char& ch) {
    auto charCode = std::toupper(ch);
    if (!(charCode >= 'A' && charCode <= 'Z')) {
        throw std::invalid_argument(Messages::INVALID_CHOICE_CHAR);
    }
    int index = charCode - 'A';
    return static_cast<uint8_t>(index < 0 ? 0 : index);
}

std::vector<unsigned short> Utils::generateIndices(const unsigned short& size, const bool& shuffle) {
    if (size == 0) {
        throw std::invalid_argument(Messages::SIZE_GT_ZERO);
    }
    auto indices = std::vector<unsigned short>(size);
    auto originalIndices = std::vector<unsigned short>(shuffle ? size : 0);
    for (unsigned short i = 0; i < size; ++i) {
        indices[i] = i;
        if (shuffle) {
            originalIndices[i] = i;
        }
    }
    // If size == 1, then we don't need to shuffle
    if (shuffle && size > 1) {
        while (true) {
            std::random_device randomDevice;
            std::mt19937 generator(randomDevice());
            std::shuffle(indices.begin(), indices.end(), generator);
            for (unsigned short i = 0; i < size; ++i) {
                if (indices[i] != originalIndices[i]) {
                    return indices;
                }
            }
        }
    }
    return indices;
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
    std::string result = str;
    result.erase(0, result.find_first_not_of(WHITESPACES));
    result.erase(result.find_last_not_of(WHITESPACES) + 1);
    return result;
}

std::string Utils::formailzeAnswer(const std::string& answer, const bool& caseSensitive) {
    std::string formalizedAnswer = Utils::trim(answer);
    if (!caseSensitive) {
        formalizedAnswer = Utils::toLower(formalizedAnswer);
    }
    return formalizedAnswer;
}
