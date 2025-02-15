#include <multiple_choice_question/answer/builder/multiple_choice_answer.builder.h>

MultipleChoiceAnswerBuilder MultipleChoiceAnswerBuilder::create() {
    return MultipleChoiceAnswerBuilder();
}

MultipleChoiceAnswerBuilder::MultipleChoiceAnswerBuilder() : answer(this->reset()) {}

MultipleChoiceAnswerBuilder& MultipleChoiceAnswerBuilder::setValue(const uint8_t& value) {
    this->answer->setValue(value);
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
    return std::make_unique<MultipleChoiceAnswer>(std::nullopt, std::nullopt);
}
