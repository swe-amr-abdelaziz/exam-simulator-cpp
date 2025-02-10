#include "multiple_choice_question.validator.h"

std::string MultipleChoiceQuestionValidator::validateText(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument(Messages::QUESTION_TEXT_CANNOT_BE_EMPTY);
    }
    if (text.length() > Enums::MAX_STRING_LENGTH) {
        throw std::invalid_argument(Messages::QUESTION_TEXT_CANNOT_BE_VERY_LONG);
    }
    return text;
}

std::unique_ptr<MultipleChoiceAnswer> MultipleChoiceQuestionValidator::validateCorrectAnswer(
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer, const std::vector<std::string>& choices) {
    if (correctAnswer->getText().has_value() && correctAnswer->getText().value() >= choices.size()) {
        throw std::invalid_argument(Messages::INVALID_MCQ_ANSWER_VALUE);
    }
    return correctAnswer;
}

std::unique_ptr<MultipleChoiceAnswer> MultipleChoiceQuestionValidator::validateStudentAnswer(
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer, const std::vector<std::string>& choices) {
    if (studentAnswer->getText().has_value() && studentAnswer->getText().value() >= choices.size()) {
        throw std::invalid_argument(Messages::INVALID_MCQ_ANSWER_VALUE);
    }
    return studentAnswer;
}

std::vector<std::string>
    MultipleChoiceQuestionValidator::validateChoices(const std::vector<std::string>& choices) {
    if (!(choices.size() >= Enums::MIN_CHOICES && choices.size() <= Enums::MAX_CHOICES)) {
        throw std::invalid_argument(Messages::INVALID_MCQ_CHOICES_RANGE);
    }
    if (MultipleChoiceQuestionValidator::includesEmptyChoice(choices)) {
        throw std::invalid_argument(Messages::CHOICES_CANNOT_BE_EMPTY);
    }
    if (MultipleChoiceQuestionValidator::includesVeryLongChoice(choices)) {
        throw std::invalid_argument(Messages::CHOICES_CANNOT_BE_VERY_LONG);
    }
    if (MultipleChoiceQuestionValidator::includesDuplicateChoice(choices)) {
        throw std::invalid_argument(Messages::CHOICES_CANNOT_HAVE_DUPLICATES);
    }
    return choices;
}

bool MultipleChoiceQuestionValidator::includesEmptyChoice(const std::vector<std::string>& choices) {
    return std::any_of(choices.begin(), choices.end(), [](const std::string& s) { return s.empty(); });
}

bool MultipleChoiceQuestionValidator::includesVeryLongChoice(const std::vector<std::string>& choices) {
    return std::any_of(choices.begin(), choices.end(),
                       [](const std::string& s) { return s.length() > Enums::MAX_STRING_LENGTH; });
}

bool MultipleChoiceQuestionValidator::includesDuplicateChoice(const std::vector<std::string>& choices) {
    return std::unordered_set<std::string>(choices.begin(), choices.end()).size() != choices.size();
}
