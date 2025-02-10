#ifndef MULTIPLE_CHOICE_QUESTION_BUILDER_H
#define MULTIPLE_CHOICE_QUESTION_BUILDER_H

#include "../multiple_choice_question.h"

class MultipleChoiceQuestionBuilder : public IBuilder<std::unique_ptr<MultipleChoiceQuestion>> {
public:
    static MultipleChoiceQuestionBuilder create();
    ~MultipleChoiceQuestionBuilder() override = default;
    MultipleChoiceQuestionBuilder& setText(const std::string& text);
    MultipleChoiceQuestionBuilder& setCorrectAnswer(std::unique_ptr<MultipleChoiceAnswer>&& correctAnswer);
    MultipleChoiceQuestionBuilder& setStudentAnswer(std::unique_ptr<MultipleChoiceAnswer>&& studentAnswer);
    MultipleChoiceQuestionBuilder& setChoices(const std::vector<std::string>& choices);
    std::unique_ptr<MultipleChoiceQuestion> build() override;

private:
    MultipleChoiceQuestionBuilder();
    std::unique_ptr<MultipleChoiceQuestion> question;
    std::unique_ptr<MultipleChoiceQuestion> reset();
};

#endif // MULTIPLE_CHOICE_QUESTION_BUILDER_H
