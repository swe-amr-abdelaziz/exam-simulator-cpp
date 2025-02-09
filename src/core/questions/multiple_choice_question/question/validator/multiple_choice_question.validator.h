#ifndef MULTIPLE_CHOICE_QUESTION_VALIDATOR_H
#define MULTIPLE_CHOICE_QUESTION_VALIDATOR_H

#include "../../../../../shared/constants/enums.h"
#include "../../answer/builder/multiple_choice_answer.builder.h"
#include "../../answer/multiple_choice_answer.h"
#include <unordered_set>

class MultipleChoiceQuestionValidator {
public:
    static std::string validateText(const std::string& text);
    static std::unique_ptr<MultipleChoiceAnswer>
        validateCorrectAnswer(std::unique_ptr<MultipleChoiceAnswer> correctAnswer,
                              const std::vector<std::string>& choices);
    static std::unique_ptr<MultipleChoiceAnswer>
        validateStudentAnswer(std::unique_ptr<MultipleChoiceAnswer> studentAnswer,
                              const std::vector<std::string>& choices);
    static std::vector<std::string> validateChoices(const std::vector<std::string>& choices);

private:
    static bool includesEmptyChoice(const std::vector<std::string>& choices);
    static bool includesVeryLongChoice(const std::vector<std::string>& choices);
    static bool includesDuplicateChoice(const std::vector<std::string>& choices);
};

#endif // MULTIPLE_CHOICE_QUESTION_VALIDATOR_H
