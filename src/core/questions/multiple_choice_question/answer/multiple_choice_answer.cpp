#include "multiple_choice_answer.h"

MultipleChoiceAnswer::MultipleChoiceAnswer(std::optional<uint8_t> text, std::optional<double> degree)
    : Answer<uint8_t, double>() {
    if (text.has_value()) {
        this->setText(text.value());
    }
    if (degree.has_value()) {
        this->setDegree(degree.value());
    }
}

void MultipleChoiceAnswer::setText(const uint8_t& text) {
    this->text = MultipleChoiceAnswerValidator::validateText(text);
}

std::optional<uint8_t> MultipleChoiceAnswer::getText() {
    return this->text;
}

void MultipleChoiceAnswer::setDegree(const double& degree) {
    this->degree = MultipleChoiceAnswerValidator::validateDergree(degree);
}

std::optional<double> MultipleChoiceAnswer::getDegree() {
    return this->degree;
}
