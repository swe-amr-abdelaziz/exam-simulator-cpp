#ifndef MULTIPLE_CHOICE_QUESTION_H
#define MULTIPLE_CHOICE_QUESTION_H

#include "../../base_question/question/base_question.h"
#include "../answer/multiple_choice_answer.h"
#include <tuple>
#include <vector>

class MultipleChoiceQuestion : public Question<MultipleChoiceAnswer> {
public:
    MultipleChoiceQuestion(std::string text, std::unique_ptr<MultipleChoiceAnswer> correctAnswer,
                           std::unique_ptr<MultipleChoiceAnswer> studentAnswer,
                           std::vector<std::string> choices = {});
    ~MultipleChoiceQuestion();
    bool isCorrect() override;
    std::string ask(const unsigned short& index) override;
    void printWithCorrection(const unsigned short& index) override;
    void shuffleAnswers();

private:
    std::vector<std::string> choices;
    std::tuple<std::string, std::vector<std::string>>
        getQuestionTextWithValidAnswers(const unsigned short& index);
    void calculateStudentDegree() override;
};

#endif // MULTIPLE_CHOICE_QUESTION_H
