#ifndef MULTIPLE_CHOICE_ANSWER_H
#define MULTIPLE_CHOICE_ANSWER_H

#include "../base_question/base_answer.h"
#include "gmock/gmock.h"
#include <algorithm>

class MultipleChoiceAnswer : public Answer<uint8_t, double> {
public:
    MultipleChoiceAnswer(const std::vector<std::string>& choices, std::optional<uint8_t> text = std::nullopt,
                         std::optional<double> degree = std::nullopt);
    ~MultipleChoiceAnswer();
    void setText(uint8_t text);
    std::optional<uint8_t> getText();
    void setDegree(double degree);
    std::optional<double> getDegree();
    void setChoices(std::vector<std::string> choices);
    std::vector<std::string> getChoices();

private:
    std::vector<std::string> choices;
    static std::vector<std::string> validateChoices(const std::vector<std::string>& choices);
};

#endif // MULTIPLE_CHOICE_ANSWER_H
