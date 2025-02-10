#include "multiple_choice_answer.h"

MultipleChoiceAnswer::MultipleChoiceAnswer(std::optional<uint8_t> value, std::optional<double> degree)
    : Answer<uint8_t, double>() {
    if (value.has_value()) {
        this->setValue(value.value());
    }
    if (degree.has_value()) {
        this->setDegree(degree.value());
    }
}

void MultipleChoiceAnswer::setValue(const uint8_t& value) {
    this->value = MultipleChoiceAnswerValidator::validateValue(value);
}

std::optional<uint8_t> MultipleChoiceAnswer::getValue() {
    return this->value;
}

void MultipleChoiceAnswer::setDegree(const double& degree) {
    this->degree = MultipleChoiceAnswerValidator::validateDergree(degree);
}

std::optional<double> MultipleChoiceAnswer::getDegree() {
    return this->degree;
}

std::unique_ptr<MultipleChoiceAnswer> MultipleChoiceAnswer::clone() const {
    return std::make_unique<MultipleChoiceAnswer>(this->value, this->degree);
}
