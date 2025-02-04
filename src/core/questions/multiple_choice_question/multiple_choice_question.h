#ifndef MULTIPLE_CHOICE_QUESTION_H
#define MULTIPLE_CHOICE_QUESTION_H

#include "../base_question/base_question.h"
#include "multiple_choice_answer.h"
#include <tuple>
#include <vector>

class MultipleChoiceQuestion : public Question<MultipleChoiceAnswer> {
public:
    MultipleChoiceQuestion(std::string text, std::unique_ptr<MultipleChoiceAnswer> correctAnswer,
                           std::unique_ptr<MultipleChoiceAnswer> studentAnswer,
                           std::vector<std::string> choices = {});
    ~MultipleChoiceQuestion();
    bool isCorrect() override;

private:
    std::vector<std::string> choices;
    void calculateStudentDegree() override;
};

#endif // MULTIPLE_CHOICE_QUESTION_H
