#include <constants/messages.h>
#include <multiple_choice_question/answer/validator/multiple_choice_answer.validator.h>
#include <utils/utils.h>

uint8_t MultipleChoiceAnswerValidator::validateValue(const uint8_t& value) {
    if (value > Utils::convertChoiceCharToIndex('Z')) {
        throw std::invalid_argument(Messages::INVALID_CHAR_INDEX);
    }
    return value;
}

double MultipleChoiceAnswerValidator::validateDergree(const double& degree) {
    if (degree < 0) {
        throw std::invalid_argument(Messages::INVALID_DEGREE);
    }
    return degree;
}
