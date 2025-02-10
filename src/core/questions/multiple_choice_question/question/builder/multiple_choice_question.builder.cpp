#include "multiple_choice_question.builder.h"

MultipleChoiceQuestionBuilder MultipleChoiceQuestionBuilder::create() {
    return MultipleChoiceQuestionBuilder();
}

MultipleChoiceQuestionBuilder::MultipleChoiceQuestionBuilder() : question(this->reset()) {}

MultipleChoiceQuestionBuilder& MultipleChoiceQuestionBuilder::setText(const std::string& text) {
    this->question->setText(text);
    return *this;
}

MultipleChoiceQuestionBuilder&
    MultipleChoiceQuestionBuilder::setCorrectAnswer(std::unique_ptr<MultipleChoiceAnswer>&& correctAnswer) {
    this->question->setCorrectAnswer(std::move(correctAnswer));
    return *this;
}

MultipleChoiceQuestionBuilder&
    MultipleChoiceQuestionBuilder::setStudentAnswer(std::unique_ptr<MultipleChoiceAnswer>&& studentAnswer) {
    this->question->setStudentAnswer(std::move(studentAnswer));
    return *this;
}

MultipleChoiceQuestionBuilder&
    MultipleChoiceQuestionBuilder::setChoices(const std::vector<std::string>& choices) {
    this->question->setChoices(choices);
    return *this;
}

std::unique_ptr<MultipleChoiceQuestion> MultipleChoiceQuestionBuilder::build() {
    return std::move(this->question);
}

std::unique_ptr<MultipleChoiceQuestion> MultipleChoiceQuestionBuilder::reset() {
    auto correctAnswer = MultipleChoiceAnswerBuilder::create().build();
    auto studentAnswer = MultipleChoiceAnswerBuilder::create().build();
    return std::make_unique<MultipleChoiceQuestion>(TestDefaults::MCQ_TEXT, std::move(correctAnswer),
                                                    std::move(studentAnswer), TestDefaults::CHOICES);
}
