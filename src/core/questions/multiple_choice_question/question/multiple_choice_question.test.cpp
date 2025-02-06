#include "multiple_choice_question.h"

static std::vector<std::string> choices = {"Cairo", "Giza", "Alexandria", "Mansoura", "Luxor"};
static uint8_t correctAnswerIndex = Utils::convertChoiceCharToIndex('A');
static double correctAnswerDegree = 5;

TEST(IsCorrectTest, given_mcq_data_with_correct_student_answer_then_mcq_is_correct) {
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 0, 5);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 0);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), choices);
    EXPECT_TRUE(question->isCorrect());
}

TEST(IsCorrectTest, given_mcq_data_with_incorrect_student_answer_then_mcq_is_incorrect) {
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 0, 5);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(choices, 2);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), choices);
    EXPECT_FALSE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_three_choices_then_correct_answer_is_provided_in_lowercase) {
    std::vector<std::string> subChoices(&choices[0], &choices[3]);
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex, correctAnswerDegree);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), subChoices);
    uint8_t questionIndex = 4;
    std::string studentAnswerText = "a";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerText, question.get(), questionIndex);
    std::string expectedOutput = R"(5. What is the capital of Egypt?
   A. Cairo
   B. Giza
   C. Alexandria
)";
    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_TRUE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_four_choices_then_correct_answer_is_provided_in_uppercase) {
    std::vector<std::string> subChoices(&choices[0], &choices[4]);
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex, correctAnswerDegree);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), subChoices);
    uint8_t questionIndex = 16;
    std::string studentAnswerText = "A";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerText, question.get(), questionIndex);
    std::string expectedOutput = R"(17. What is the capital of Egypt?
    A. Cairo
    B. Giza
    C. Alexandria
    D. Mansoura
)";
    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_TRUE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_five_choices_then_incorrect_answer_is_provided_in_lowercase) {
    std::vector<std::string> subChoices(&choices[0], &choices[5]);
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex, correctAnswerDegree);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), subChoices);
    uint8_t questionIndex = 52;
    std::string studentAnswerText = "b";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerText, question.get(), questionIndex);
    std::string expectedOutput = R"(53. What is the capital of Egypt?
    A. Cairo
    B. Giza
    C. Alexandria
    D. Mansoura
    E. Luxor
)";
    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_five_choices_then_incorrect_answer_is_provided_in_uppercase) {
    std::vector<std::string> subChoices(&choices[0], &choices[5]);
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex, correctAnswerDegree);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), subChoices);
    uint8_t questionIndex = 99;
    std::string studentAnswerText = "C";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerText, question.get(), questionIndex);
    std::string expectedOutput = R"(100. What is the capital of Egypt?
     A. Cairo
     B. Giza
     C. Alexandria
     D. Mansoura
     E. Luxor
)";
    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}
