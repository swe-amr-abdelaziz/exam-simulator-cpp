#ifndef MULTIPLE_CHOICE_ANSWER_H
#define MULTIPLE_CHOICE_ANSWER_H

#include "../../../../shared/interfaces/cloneable.interface.h"
#include "../../base_question/answer/base_answer.h"
#include "validator/multiple_choice_answer.validator.h"

class MultipleChoiceAnswer : public Answer<uint8_t, double>, public ICloneable<MultipleChoiceAnswer> {
public:
    MultipleChoiceAnswer(std::optional<uint8_t> value = std::nullopt,
                         std::optional<double> degree = std::nullopt);
    ~MultipleChoiceAnswer() = default;
    void setValue(const uint8_t& value) override;
    std::optional<uint8_t> getValue() override;
    void setDegree(const double& degree) override;
    std::optional<double> getDegree() override;
    std::unique_ptr<MultipleChoiceAnswer> clone() const override;
};

#endif // MULTIPLE_CHOICE_ANSWER_H
