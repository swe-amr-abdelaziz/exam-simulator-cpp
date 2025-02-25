#ifndef MULTIPLE_CHOICE_ANSWER_BUILDER_H
#define MULTIPLE_CHOICE_ANSWER_BUILDER_H

#include <interfaces/builder.interface.h>
#include <multiple_choice_question/answer/multiple_choice_answer.h>

class MultipleChoiceAnswerBuilder : public IBuilder<std::unique_ptr<MultipleChoiceAnswer>> {
public:
    static MultipleChoiceAnswerBuilder create();
    ~MultipleChoiceAnswerBuilder() override = default;
    MultipleChoiceAnswerBuilder& setValue(const uint8_t& value);
    MultipleChoiceAnswerBuilder& setDegree(const double& degree);
    std::unique_ptr<MultipleChoiceAnswer> build() override;

private:
    MultipleChoiceAnswerBuilder();
    std::unique_ptr<MultipleChoiceAnswer> answer;
    std::unique_ptr<MultipleChoiceAnswer> reset();
};

#endif // MULTIPLE_CHOICE_ANSWER_BUILDER_H
