#ifndef BASE_QUESTION_H
#define BASE_QUESTION_H

#include <memory>

#include <constants/enums.h>
#include <interfaces/quesiton.interface.h>

template <class T>
class Question : public IQuestion {
public:
    Question(std::string text, Enums::QuestionType type, std::unique_ptr<T> correctAnswer,
             std::unique_ptr<T> studentAnswer = nullptr)
        : text(text), type(type), correctAnswer(std::move(correctAnswer)),
          studentAnswer(std::move(studentAnswer)) {}
    virtual ~Question() {}
    virtual bool isCorrect() override = 0;
    virtual void ask(const unsigned short& index) override = 0;
    virtual void printWithCorrection(const unsigned short& index) override = 0;

protected:
    std::string text;
    Enums::QuestionType type;
    std::unique_ptr<T> correctAnswer;
    std::unique_ptr<T> studentAnswer;
    virtual void calculateStudentDegree() = 0;
};

#endif // BASE_QUESTION_H
