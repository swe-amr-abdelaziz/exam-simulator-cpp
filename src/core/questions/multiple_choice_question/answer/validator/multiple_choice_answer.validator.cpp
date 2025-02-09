#include "multiple_choice_answer.validator.h"

uint8_t MultipleChoiceAnswerValidator::validateText(const uint8_t& text) {
    if (text > Utils::convertChoiceCharToIndex('Z')) {
        throw std::invalid_argument(Messages::INVALID_CHAR_INDEX);
    }
    return text;
}

double MultipleChoiceAnswerValidator::validateDergree(const double& degree) {
    if (degree < 0) {
        throw std::invalid_argument(Messages::INVALID_DEGREE);
    }
    return degree;
}
