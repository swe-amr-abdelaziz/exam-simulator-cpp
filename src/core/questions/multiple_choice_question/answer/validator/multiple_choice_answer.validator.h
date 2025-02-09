#ifndef MULTIPLE_CHOICE_ANSWER_VALIDATOR_H
#define MULTIPLE_CHOICE_ANSWER_VALIDATOR_H

#include "../../../../../shared/utils/utils.h"

class MultipleChoiceAnswerValidator {
public:
    static uint8_t validateText(const uint8_t& text);
    static double validateDergree(const double& degree);
};

#endif // MULTIPLE_CHOICE_ANSWER_VALIDATOR_H
