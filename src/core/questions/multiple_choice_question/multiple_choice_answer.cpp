#include "multiple_choice_answer.h"

MultipleChoiceAnswer::MultipleChoiceAnswer(const std::vector<std::string>& choices,
                                           std::optional<uint8_t> text, std::optional<double> degree)
    : Answer<uint8_t, double>(), choices(validateChoices(choices)) {
    if (text.has_value()) {
        this->setText(text.value());
    }
    if (degree.has_value()) {
        this->setDegree(degree.value());
    }
}

MultipleChoiceAnswer::~MultipleChoiceAnswer() {}

std::vector<std::string> MultipleChoiceAnswer::validateChoices(const std::vector<std::string>& choices) {
    if (!(choices.size() >= 3 && choices.size() <= 5)) {
        throw std::invalid_argument("Choices must be between 3 and 5 elements");
    }
    return choices;
}

void MultipleChoiceAnswer::setChoices(std::vector<std::string> choices) {
    this->choices = this->validateChoices(choices);
}

std::vector<std::string> MultipleChoiceAnswer::getChoices() {
    return this->choices;
}

void MultipleChoiceAnswer::setText(uint8_t text) {
    if (text >= this->choices.size()) {
        throw std::invalid_argument("Answer text must be one of the provided choices");
    }
    this->text = text;
}

std::optional<uint8_t> MultipleChoiceAnswer::getText() {
    return this->text;
}

void MultipleChoiceAnswer::setDegree(double degree) {
    if (degree < 0) {
        throw std::invalid_argument("Degree must be greater than or equal to zero");
    }
    this->degree = degree;
}

std::optional<double> MultipleChoiceAnswer::getDegree() {
    return this->degree;
}
