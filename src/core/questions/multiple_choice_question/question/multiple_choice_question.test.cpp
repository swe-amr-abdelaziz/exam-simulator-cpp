#include "builder/multiple_choice_question.builder.h"

static auto getCorrectAnswerInstance() {
    return MultipleChoiceAnswerBuilder::create()
        .setValue(MCQ_CORRECT_ANSWER_VALUE)
        .setDegree(MCQ_CORRECT_ANSWER_DEGREE)
        .build();
}

static auto getStudentAnswerInstance() {
    return MultipleChoiceAnswerBuilder::create().build();
}

static auto getQestionInstance() {
    return MultipleChoiceQuestionBuilder::create()
        .setText(MCQ_TEXT)
        .setCorrectAnswer(std::move(getCorrectAnswerInstance()))
        .setStudentAnswer(std::move(getStudentAnswerInstance()))
        .setChoices(CHOICES)
        .build();
}

TEST(GetTextTest, should_return_question_text_when_text_is_set) {
    auto question = getQestionInstance();
    EXPECT_EQ(question->getText(), MCQ_TEXT);
}

TEST(SetTextTest, should_return_new_question_text_when_text_is_set) {
    auto question = getQestionInstance();
    std::string text = "What is the capital of the United States?";
    question->setText(text);
    EXPECT_EQ(question->getText(), text);
}

TEST(GetCorrectAnswerTest, should_return_question_correct_answer_when_correct_answer_is_set) {
    auto question = getQestionInstance();
    EXPECT_EQ(question->getCorrectAnswer()->getValue(), MCQ_CORRECT_ANSWER_VALUE);
    EXPECT_EQ(question->getCorrectAnswer()->getDegree(), MCQ_CORRECT_ANSWER_DEGREE);
}

TEST(SetCorrectAnswerTest, should_return_new_question_correct_answer_when_correct_answer_is_set) {
    uint8_t value = 1;
    double degree = 5.0;
    auto question = getQestionInstance();
    question->setCorrectAnswer(
        MultipleChoiceAnswerBuilder::create().setValue(value).setDegree(degree).build());
    EXPECT_EQ(question->getCorrectAnswer()->getValue(), value);
    EXPECT_EQ(question->getCorrectAnswer()->getDegree(), degree);
}

TEST(GetStudentAnswerTest, should_return_question_student_answer_when_student_answer_is_set) {
    auto question = getQestionInstance();
    EXPECT_EQ(question->getStudentAnswer()->getValue(), std::nullopt);
    EXPECT_EQ(question->getStudentAnswer()->getDegree(), std::nullopt);
}

TEST(SetStudentAnswerTest, should_return_new_question_student_answer_when_student_answer_is_set) {
    uint8_t value = 1;
    double degree = 5.0;
    auto question = getQestionInstance();
    question->setStudentAnswer(
        MultipleChoiceAnswerBuilder::create().setValue(value).setDegree(degree).build());
    EXPECT_EQ(question->getStudentAnswer()->getValue(), value);
    EXPECT_EQ(question->getStudentAnswer()->getDegree(), degree);
}

TEST(GetChoicesTest, should_return_question_choices_when_choices_are_set) {
    auto question = getQestionInstance();
    EXPECT_THAT(question->getChoices(), CHOICES);
}

TEST(SetTextTest, should_return_new_question_choices_when_choices_are_set) {
    auto question = getQestionInstance();
    std::vector<std::string> choices({"A", "B", "C"});
    question->setChoices(choices);
    EXPECT_THAT(question->getChoices(), choices);
}

TEST(CloneTest, given_multiple_choice_question_with_valid_values_then_clone_is_created_and_values_are_copied) {
    std::string text = "What is the capital of Egypt?";
    uint8_t correctAnswerValue = 0;
    double correctAnswerDegree = 5;
    auto correctAnswer = MultipleChoiceAnswerBuilder::create()
                             .setValue(correctAnswerValue)
                             .setDegree(correctAnswerDegree)
                             .build();
    uint8_t studentAnswerValue = 1;
    double studentAnswerDegree = 3;
    auto studentAnswer = MultipleChoiceAnswerBuilder::create()
                             .setValue(studentAnswerValue)
                             .setDegree(studentAnswerDegree)
                             .build();
    std::vector<std::string> choices({"D", "E", "F"});

    auto questionOriginal = getQestionInstance();
    auto questionClone = questionOriginal->clone();

    questionClone->setText(text);
    questionClone->setCorrectAnswer(std::move(correctAnswer));
    questionClone->setStudentAnswer(std::move(studentAnswer));
    questionClone->setChoices(choices);

    // Validate that original question has not been modified
    EXPECT_EQ(questionOriginal->getText(), MCQ_TEXT);
    EXPECT_EQ(questionOriginal->getCorrectAnswer()->getValue(), MCQ_CORRECT_ANSWER_VALUE);
    EXPECT_EQ(questionOriginal->getCorrectAnswer()->getDegree(), MCQ_CORRECT_ANSWER_DEGREE);
    EXPECT_EQ(questionOriginal->getStudentAnswer()->getValue(), std::nullopt);
    EXPECT_EQ(questionOriginal->getStudentAnswer()->getDegree(), std::nullopt);
    EXPECT_THAT(questionOriginal->getChoices(), testing::ElementsAreArray(CHOICES));

    // Validate that cloned question has new values
    EXPECT_EQ(questionClone->getText(), text);
    EXPECT_EQ(questionClone->getCorrectAnswer()->getValue(), correctAnswerValue);
    EXPECT_EQ(questionClone->getCorrectAnswer()->getDegree(), correctAnswerDegree);
    EXPECT_EQ(questionClone->getStudentAnswer()->getValue(), studentAnswerValue);
    EXPECT_EQ(questionClone->getStudentAnswer()->getDegree(), studentAnswerDegree);
    EXPECT_THAT(questionClone->getChoices(), testing::ElementsAreArray(choices));
}

TEST(IsCorrectTest, should_return_false_when_student_answer_is_left_empty) {
    auto correctAnswer = getCorrectAnswerInstance();
    auto studentAnswer = MultipleChoiceAnswerBuilder::create().build();
    auto question = MultipleChoiceQuestionBuilder::create()
                        .setText(MCQ_TEXT)
                        .setCorrectAnswer(std::move(correctAnswer))
                        .setStudentAnswer(std::move(studentAnswer))
                        .setChoices(CHOICES)
                        .build();

    EXPECT_FALSE(question->isCorrect());
}

TEST(IsCorrectTest, should_return_false_when_student_answer_is_not_the_same_as_correct_answer) {
    uint8_t value = 1;
    auto correctAnswer = getCorrectAnswerInstance();
    auto studentAnswer = MultipleChoiceAnswerBuilder::create().setValue(value).build();
    auto question = MultipleChoiceQuestionBuilder::create()
                        .setText(MCQ_TEXT)
                        .setCorrectAnswer(std::move(correctAnswer))
                        .setStudentAnswer(std::move(studentAnswer))
                        .setChoices(CHOICES)
                        .build();

    EXPECT_FALSE(question->isCorrect());
}

TEST(IsCorrectTest, should_return_true_when_student_answer_is_the_same_as_correct_answer) {
    auto correctAnswer = getCorrectAnswerInstance();
    auto studentAnswer = MultipleChoiceAnswerBuilder::create().setValue(MCQ_CORRECT_ANSWER_VALUE).build();
    auto question = MultipleChoiceQuestionBuilder::create()
                        .setText(MCQ_TEXT)
                        .setCorrectAnswer(std::move(correctAnswer))
                        .setStudentAnswer(std::move(studentAnswer))
                        .setChoices(CHOICES)
                        .build();

    EXPECT_TRUE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_three_choices_then_correct_answer_is_provided_in_lowercase) {
    auto question = getQestionInstance();
    std::vector<std::string> subChoices(&CHOICES[0], &CHOICES[3]);
    question->setChoices(subChoices);
    uint8_t questionIndex = 4;
    std::string studentAnswerValue = "a";

    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerValue, question.get(), questionIndex);
    std::string expectedOutput = R"(5. What is the name of the first month of the year?
   A. January
   B. February
   C. March
)";

    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_TRUE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_four_choices_then_correct_answer_is_provided_in_uppercase) {
    auto question = getQestionInstance();
    std::vector<std::string> subChoices(&CHOICES[0], &CHOICES[4]);
    question->setChoices(subChoices);
    uint8_t questionIndex = 16;
    std::string studentAnswerValue = "A";

    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerValue, question.get(), questionIndex);
    std::string expectedOutput = R"(17. What is the name of the first month of the year?
    A. January
    B. February
    C. March
    D. April
)";

    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_TRUE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_five_choices_then_incorrect_answer_is_provided_in_lowercase) {
    auto question = getQestionInstance();
    uint8_t questionIndex = 52;
    std::string studentAnswerValue = "b";

    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerValue, question.get(), questionIndex);
    std::string expectedOutput = R"(53. What is the name of the first month of the year?
    A. January
    B. February
    C. March
    D. April
    E. May
)";

    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}

TEST(AskTest, given_mcq_data_with_five_choices_then_incorrect_answer_is_provided_in_uppercase) {
    auto question = getQestionInstance();
    uint8_t questionIndex = 99;
    std::string studentAnswerValue = "C";

    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerValue, question.get(), questionIndex);
    std::string expectedOutput = R"(100. What is the name of the first month of the year?
     A. January
     B. February
     C. March
     D. April
     E. May
)";

    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}

TEST(PrintWithCorrectionTest,
     given_mcq_data_with_three_choices_and_correct_answer_is_provided_then_throws_exception) {
    EXPECT_THROW(
        {
            try {
                auto question = getQestionInstance();
                std::vector<std::string> subChoices(&CHOICES[0], &CHOICES[3]);
                question->setChoices(subChoices);
                question->setStudentAnswer(
                    MultipleChoiceAnswerBuilder::create().setValue(MCQ_CORRECT_ANSWER_VALUE).build());
                uint8_t questionIndex = 5;
                question->printWithCorrection(questionIndex);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::METHOD_CANNOT_BE_CALLED_WITH_CORRECT_ANSWER, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(PrintWithCorrectionTest,
     given_mcq_data_with_four_choices_and_incorrect_answer_is_provided_then_prints_the_answer_feedback) {
    auto question = getQestionInstance();
    std::vector<std::string> subChoices(&CHOICES[0], &CHOICES[4]);
    question->setChoices(subChoices);
    auto studentAnswerIndex = Utils::convertChoiceCharToIndex('c');
    question->setStudentAnswer(MultipleChoiceAnswerBuilder::create().setValue(studentAnswerIndex).build());
    uint8_t questionIndex = 10;

    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::printWithCorrection, "\n", question.get(), questionIndex);
    std::string expectedOutput = R"(11. What is the name of the first month of the year?
    A. January  ✅
    B. February
    C. March  ❌
    D. April

Press enter to continue
)";

    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}

TEST(PrintWithCorrectionTest,
     given_mcq_data_with_five_choices_and_incorrect_answer_is_provided_then_prints_the_answer_feedback) {
    auto question = getQestionInstance();
    auto studentAnswerIndex = Utils::convertChoiceCharToIndex('e');
    question->setStudentAnswer(MultipleChoiceAnswerBuilder::create().setValue(studentAnswerIndex).build());
    uint8_t questionIndex = 100;

    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::printWithCorrection, "\n", question.get(), questionIndex);
    std::string expectedOutput = R"(101. What is the name of the first month of the year?
     A. January  ✅
     B. February
     C. March
     D. April
     E. May  ❌

Press enter to continue
)";

    EXPECT_EQ(consoleOutput, expectedOutput);
    EXPECT_FALSE(question->isCorrect());
}

TEST(shuffleAnswersTest,
     given_mcq_data_with_five_choices_with_shuffled_answers_then_evaluate_student_answer_correctness) {
    auto question = getQestionInstance();
    question->shuffleAnswers();
    uint8_t questionIndex = 0;
    std::string studentAnswerValue = "A";

    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(&IQuestion::ask, studentAnswerValue, question.get(), questionIndex);

    // Validate that the prompt includes the question heading and the unordered list of choices
    ASSERT_THAT(consoleOutput, testing::HasSubstr(MCQ_TEXT));
    ASSERT_THAT(consoleOutput, testing::HasSubstr(CHOICES[0]));
    ASSERT_THAT(consoleOutput, testing::HasSubstr(CHOICES[1]));
    ASSERT_THAT(consoleOutput, testing::HasSubstr(CHOICES[2]));
    ASSERT_THAT(consoleOutput, testing::HasSubstr(CHOICES[3]));
    ASSERT_THAT(consoleOutput, testing::HasSubstr(CHOICES[4]));

    // Evaluate the correctness of the student's answer
    auto consoleOutputSplitted = Utils::split(consoleOutput, '\n');
    auto step = 1; // because the question heading is not counted
    auto it = std::find_if(consoleOutputSplitted.begin() + step, consoleOutputSplitted.end(),
                           [](const std::string& line) {
                               return line.find(CHOICES[0]) != std::string::npos;
                           });
    auto correctAnswerIndex =
        static_cast<uint8_t>(std::distance(consoleOutputSplitted.begin() + step, it));
    auto studentAnswerIndex = Utils::convertChoiceCharToIndex(studentAnswerValue[0]);
    if (correctAnswerIndex == studentAnswerIndex) {
        EXPECT_TRUE(question->isCorrect());
    } else {
        EXPECT_FALSE(question->isCorrect());
    }
}
