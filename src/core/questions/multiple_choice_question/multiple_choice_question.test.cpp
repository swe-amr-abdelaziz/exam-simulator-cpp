#include "multiple_choice_question.h"

static std::vector<std::string> choices = {"Cairo", "Alexandria", "Giza", "Luxor"};

TEST(MultipleChoiceQuestionTest, given_mcq_data_with_correct_student_answer_then_mcq_is_correct) {
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 0, 5);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 0);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), choices);
    EXPECT_TRUE(question->isCorrect());
}

TEST(MultipleChoiceQuestionTest, given_mcq_data_with_incorrect_student_answer_then_mcq_is_incorrect) {
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 0, 5);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 2);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), choices);
    EXPECT_FALSE(question->isCorrect());
}
