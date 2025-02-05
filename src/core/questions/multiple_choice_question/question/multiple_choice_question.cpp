#include "multiple_choice_question.h"

MultipleChoiceQuestion::MultipleChoiceQuestion(std::string text,
                                               std::unique_ptr<MultipleChoiceAnswer> correctAnswer,
                                               std::unique_ptr<MultipleChoiceAnswer> studentAnswer,
                                               std::vector<std::string> choices)
    : Question<MultipleChoiceAnswer>(text, QuestionType::MCQ, std::move(correctAnswer),
                                     std::move(studentAnswer)),
      choices(std::move(choices)) {}

MultipleChoiceQuestion::~MultipleChoiceQuestion() {}

bool MultipleChoiceQuestion::isCorrect() {
    if (!this->studentAnswer->getDegree().has_value()) {
        this->calculateStudentDegree();
    }
    return this->studentAnswer->getDegree().value() == this->correctAnswer->getDegree().value();
}

std::string MultipleChoiceQuestion::ask(const unsigned short& index) {
    this->studentAnswer->setDegree((double) index);
    return this->text;
}

void MultipleChoiceQuestion::printWithCorrection(const unsigned short& index) {
    this->studentAnswer->setDegree((double) index);
}

void MultipleChoiceQuestion::shuffleAnswers() {}

std::tuple<std::string, std::vector<std::string>>
    MultipleChoiceQuestion::getQuestionTextWithValidAnswers(const unsigned short& index) {
    this->studentAnswer->setDegree((double) index);
    std::vector<std::string> validAnswers;
    return std::make_tuple("", validAnswers);
}

void MultipleChoiceQuestion::calculateStudentDegree() {
    double studentDegree = this->studentAnswer->getText().value() == this->correctAnswer->getText().value()
                               ? this->correctAnswer->getDegree().value()
                               : 0;
    this->studentAnswer->setDegree(studentDegree);
}
