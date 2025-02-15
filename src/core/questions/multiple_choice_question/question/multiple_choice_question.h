#ifndef MULTIPLE_CHOICE_QUESTION_H
#define MULTIPLE_CHOICE_QUESTION_H

#include <base_question/question/base_question.h>
#include <multiple_choice_question/answer/multiple_choice_answer.h>

class MultipleChoiceQuestion : public Question<MultipleChoiceAnswer>, ICloneable<MultipleChoiceQuestion> {
public:
    MultipleChoiceQuestion(std::string text, std::unique_ptr<MultipleChoiceAnswer> correctAnswer,
                           std::unique_ptr<MultipleChoiceAnswer> studentAnswer,
                           std::vector<std::string> choices);
    ~MultipleChoiceQuestion() = default;
    bool isCorrect() override;
    void ask(const unsigned short& index) override;
    void printWithCorrection(const unsigned short& index) override;
    void shuffleAnswers();

    void setText(const std::string& text);
    std::string getText() const;
    void setCorrectAnswer(std::unique_ptr<MultipleChoiceAnswer> correctAnswer);
    std::unique_ptr<MultipleChoiceAnswer> getCorrectAnswer() const;
    void setStudentAnswer(std::unique_ptr<MultipleChoiceAnswer> studentAnswer);
    std::unique_ptr<MultipleChoiceAnswer> getStudentAnswer() const;
    void setChoices(const std::vector<std::string>& choices);
    std::vector<std::string> getChoices() const;
    std::unique_ptr<MultipleChoiceQuestion> clone() const override;

private:
    std::vector<std::string> choices;
    std::tuple<std::string, std::vector<std::string>>
        getQuestionTextWithValidAnswers(const unsigned short& index, bool withCorrection = false);
    void calculateStudentDegree() override;
};

#endif // MULTIPLE_CHOICE_QUESTION_H
