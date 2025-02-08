#include "multiple_choice_answer.builder.h"

MultipleChoiceAnswerBuilder MultipleChoiceAnswerBuilder::create() {
    return MultipleChoiceAnswerBuilder();
}

MultipleChoiceAnswerBuilder::MultipleChoiceAnswerBuilder() : answer(this->reset()) {}

MultipleChoiceAnswerBuilder& MultipleChoiceAnswerBuilder::setChoices(const std::vector<std::string>& choices) {
    this->answer->setChoices(choices);
    return *this;
}

MultipleChoiceAnswerBuilder& MultipleChoiceAnswerBuilder::setText(const uint8_t& text) {
    this->answer->setText(text);
    return *this;
}

MultipleChoiceAnswerBuilder& MultipleChoiceAnswerBuilder::setDegree(const double& degree) {
    this->answer->setDegree(degree);
    return *this;
}

std::unique_ptr<MultipleChoiceAnswer> MultipleChoiceAnswerBuilder::build() {
    return std::move(this->answer);
}

std::unique_ptr<MultipleChoiceAnswer> MultipleChoiceAnswerBuilder::reset() {
    return std::make_unique<MultipleChoiceAnswer>(this->defaultChoices, this->defaultText,
                                                  this->defaultDegree);
}
