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

TEST(PrintWithCorrectionTest,
     given_mcq_data_with_three_choices_and_correct_answer_is_provided_then_throws_exception) {
    EXPECT_THROW(
        {
            try {
                std::vector<std::string> subChoices(&choices[0], &choices[3]);
                std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
                    std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex,
                                                           correctAnswerDegree);
                auto studentAnswerIndex = Utils::convertChoiceCharToIndex('a');
                std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
                    std::make_unique<MultipleChoiceAnswer>(subChoices, studentAnswerIndex);
                std::unique_ptr<IQuestion> question =
                    std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?",
                                                             std::move(correctAnswer),
                                                             std::move(studentAnswer), subChoices);
                uint8_t questionIndex = 5;
                question->printWithCorrection(questionIndex);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("This method should not be called when the student answer is correct",
                             ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(PrintWithCorrectionTest,
     given_mcq_data_with_four_choices_and_incorrect_answer_is_provided_then_prints_the_answer_feedback) {
    std::vector<std::string> subChoices(&choices[0], &choices[4]);
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex, correctAnswerDegree);
    auto studentAnswerIndex = Utils::convertChoiceCharToIndex('c');
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, studentAnswerIndex);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), subChoices);
    uint8_t questionIndex = 10;
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::printWithCorrection, "\n", question.get(), questionIndex);
    std::string expectedOutput = R"(11. What is the capital of Egypt?
    A. Cairo  ✅
    B. Giza
    C. Alexandria  ❌
    D. Mansoura

Press enter to continue
)";
    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}

TEST(PrintWithCorrectionTest,
     given_mcq_data_with_five_choices_and_incorrect_answer_is_provided_then_prints_the_answer_feedback) {
    std::vector<std::string> subChoices(&choices[0], &choices[5]);
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex, correctAnswerDegree);
    auto studentAnswerIndex = Utils::convertChoiceCharToIndex('e');
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, studentAnswerIndex);
    std::unique_ptr<IQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), subChoices);
    uint8_t questionIndex = 100;
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::printWithCorrection, "\n", question.get(), questionIndex);
    std::string expectedOutput = R"(101. What is the capital of Egypt?
     A. Cairo  ✅
     B. Giza
     C. Alexandria
     D. Mansoura
     E. Luxor  ❌

Press enter to continue
)";
    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}

TEST(shuffleAnswersTest,
     given_mcq_data_with_five_choices_with_shuffled_answers_then_evaluate_student_answer_correctness) {
    std::vector<std::string> subChoices(&choices[0], &choices[5]);
    std::unique_ptr<MultipleChoiceAnswer> correctAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices, correctAnswerIndex, correctAnswerDegree);
    std::unique_ptr<MultipleChoiceAnswer> studentAnswer =
        std::make_unique<MultipleChoiceAnswer>(subChoices);
    std::unique_ptr<MultipleChoiceQuestion> question =
        std::make_unique<MultipleChoiceQuestion>("What is the capital of Egypt?", std::move(correctAnswer),
                                                 std::move(studentAnswer), subChoices);
    question->shuffleAnswers();
    uint8_t questionIndex = 0;
    std::string studentAnswerText = "A";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerText, question.get(), questionIndex);

    // Validate that the prompt includes the question heading and the unordered list of choices
    ASSERT_THAT(consoleOutput, testing::HasSubstr("1. What is the capital of Egypt?"));
    ASSERT_THAT(consoleOutput, testing::HasSubstr("Cairo"));
    ASSERT_THAT(consoleOutput, testing::HasSubstr("Giza"));
    ASSERT_THAT(consoleOutput, testing::HasSubstr("Alexandria"));
    ASSERT_THAT(consoleOutput, testing::HasSubstr("Mansoura"));
    ASSERT_THAT(consoleOutput, testing::HasSubstr("Luxor"));

    // Evaluate the correctness of the student's answer
    auto consoleOutputSplitted = Utils::split(consoleOutput, '\n');
    auto step = 1; // because the question heading is not counted
    auto it =
        std::find_if(consoleOutputSplitted.begin() + step, consoleOutputSplitted.end(),
                     [](const std::string& line) { return line.find("Cairo") != std::string::npos; });
    auto correctAnswerIndex =
        static_cast<uint8_t>(std::distance(consoleOutputSplitted.begin() + step, it));
    auto studentAnswerIndex = Utils::convertChoiceCharToIndex(studentAnswerText[0]);
    if (correctAnswerIndex == studentAnswerIndex) {
        EXPECT_TRUE(question->isCorrect());
    } else {
        EXPECT_FALSE(question->isCorrect());
    }
}
