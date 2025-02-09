#ifndef MULTIPLE_CHOICE_ANSWER_H
#define MULTIPLE_CHOICE_ANSWER_H

#include "../../base_question/answer/base_answer.h"
#include "validator/multiple_choice_answer.validator.h"

class MultipleChoiceAnswer : public Answer<uint8_t, double> {
public:
    MultipleChoiceAnswer(std::optional<uint8_t> text = std::nullopt,
                         std::optional<double> degree = std::nullopt);
    ~MultipleChoiceAnswer() = default;
    void setText(const uint8_t& text) override;
    std::optional<uint8_t> getText() override;
    void setDegree(const double& degree) override;
    std::optional<double> getDegree() override;
};

#endif // MULTIPLE_CHOICE_ANSWER_H
