#ifndef MULTIPLE_CHOICE_ANSWER_BUILDER_H
#define MULTIPLE_CHOICE_ANSWER_BUILDER_H

#include "../../../../../shared/constants/test_defaults.h"
#include "../../../../../shared/interfaces/builder.interface.h"
#include "../multiple_choice_answer.h"

class MultipleChoiceAnswerBuilder : public IBuilder<std::unique_ptr<MultipleChoiceAnswer>> {
public:
    static MultipleChoiceAnswerBuilder create();
    ~MultipleChoiceAnswerBuilder() override = default;
    MultipleChoiceAnswerBuilder& setChoices(const std::vector<std::string>& choices);
    MultipleChoiceAnswerBuilder& setText(const uint8_t& text);
    MultipleChoiceAnswerBuilder& setDegree(const double& degree);
    std::unique_ptr<MultipleChoiceAnswer> build() override;

private:
    MultipleChoiceAnswerBuilder();
    std::vector<std::string> defaultChoices = TestDefaults::CHOICES;
    std::optional<uint8_t> defaultText = std::nullopt;
    std::optional<double> defaultDegree = std::nullopt;
    std::unique_ptr<MultipleChoiceAnswer> answer;
    std::unique_ptr<MultipleChoiceAnswer> reset();
};

#endif // MULTIPLE_CHOICE_ANSWER_BUILDER_H
