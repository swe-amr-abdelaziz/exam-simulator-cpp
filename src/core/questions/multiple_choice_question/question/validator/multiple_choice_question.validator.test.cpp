#include "multiple_choice_question.validator.h"

TEST(ValidateTextTest, should_throw_exception_when_text_is_empty) {
    EXPECT_THROW(
        {
            try {
                std::string text = "";
                MultipleChoiceQuestionValidator::validateText(text);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::QUESTION_TEXT_CANNOT_BE_EMPTY, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateTextTest, should_throw_exception_when_text_is_longer_than_500_characters) {
    EXPECT_THROW(
        {
            try {
                std::string text = std::string(Enums::MAX_STRING_LENGTH + 1, 'a');
                MultipleChoiceQuestionValidator::validateText(text);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::QUESTION_TEXT_CANNOT_BE_VERY_LONG, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateTextTest, should_return_text_when_text_is_valid) {
    auto output = MultipleChoiceQuestionValidator::validateText(TestDefaults::MCQ_TEXT);
    EXPECT_EQ(output, TestDefaults::MCQ_TEXT);
}

TEST(ValidateCorrectAnswerTest, should_throw_exception_when_correct_answer_text_is_not_set) {
    EXPECT_THROW(
        {
            try {
                auto correctAnswer = MultipleChoiceAnswerBuilder::create()
                                         .setDegree(TestDefaults::MCQ_CORRECT_ANSWER_DEGREE)
                                         .build();
                MultipleChoiceQuestionValidator::validateCorrectAnswer(std::move(correctAnswer),
                                                                       TestDefaults::CHOICES);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::REQUIRED_MCQ_CORRECT_ANSWER_TEXT, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateCorrectAnswerTest, should_throw_exception_when_correct_answer_degree_is_not_set) {
    EXPECT_THROW(
        {
            try {
                auto correctAnswer = MultipleChoiceAnswerBuilder::create()
                                         .setText(TestDefaults::MCQ_CORRECT_ANSWER_TEXT)
                                         .build();
                MultipleChoiceQuestionValidator::validateCorrectAnswer(std::move(correctAnswer),
                                                                       TestDefaults::CHOICES);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::REQUIRED_MCQ_CORRECT_ANSWER_DEGREE, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateCorrectAnswerTest,
     should_throw_exception_when_correct_answer_value_is_greater_than_given_choices) {
    EXPECT_THROW(
        {
            try {
                auto correctAnswer = MultipleChoiceAnswerBuilder::create()
                                         .setText(static_cast<uint8_t>(TestDefaults::CHOICES.size()))
                                         .setDegree(TestDefaults::MCQ_CORRECT_ANSWER_DEGREE)
                                         .build();
                MultipleChoiceQuestionValidator::validateCorrectAnswer(std::move(correctAnswer),
                                                                       TestDefaults::CHOICES);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_MCQ_ANSWER_VALUE, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateCorrectAnswerTest, should_return_correct_answer_when_correct_answer_value_is_valid) {
    auto correctAnswer = MultipleChoiceAnswerBuilder::create()
                             .setText(TestDefaults::MCQ_CORRECT_ANSWER_TEXT)
                             .setDegree(TestDefaults::MCQ_CORRECT_ANSWER_DEGREE)
                             .build();
    auto output = MultipleChoiceQuestionValidator::validateCorrectAnswer(std::move(correctAnswer),
                                                                         TestDefaults::CHOICES);
    EXPECT_EQ(output->getText().value(), TestDefaults::MCQ_CORRECT_ANSWER_TEXT);
}

TEST(ValidateStudentAnswerTest,
     should_throw_exception_when_student_answer_value_is_greater_than_given_choices) {
    EXPECT_THROW(
        {
            try {
                auto studentAnswer = MultipleChoiceAnswerBuilder::create()
                                         .setText(static_cast<uint8_t>(TestDefaults::CHOICES.size()))
                                         .build();
                MultipleChoiceQuestionValidator::validateStudentAnswer(std::move(studentAnswer),
                                                                       TestDefaults::CHOICES);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_MCQ_ANSWER_VALUE, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateStudentAnswerTest, should_return_student_answer_when_student_answer_value_is_valid) {
    uint8_t text = 0;
    auto studentAnswer = MultipleChoiceAnswerBuilder::create().setText(text).build();
    auto output = MultipleChoiceQuestionValidator::validateStudentAnswer(std::move(studentAnswer),
                                                                         TestDefaults::CHOICES);
    EXPECT_EQ(output->getText().value(), text);
}

TEST(ValidateChoicesTest, should_throw_exception_when_choices_are_less_than_3) {
    EXPECT_THROW(
        {
            try {
                std::vector<std::string> choices(&CHOICES[0], &CHOICES[2]);
                MultipleChoiceQuestionValidator::validateChoices(choices);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_MCQ_CHOICES_RANGE, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateChoicesTest, should_throw_exception_when_choices_are_more_than_5) {
    EXPECT_THROW(
        {
            try {
                std::vector<std::string> choices(CHOICES);
                choices.push_back("dummy");
                MultipleChoiceQuestionValidator::validateChoices(choices);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_MCQ_CHOICES_RANGE, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateChoicesTest, should_throw_exception_when_choices_contains_at_least_one_empty_choice) {
    EXPECT_THROW(
        {
            try {
                std::vector<std::string> choices(CHOICES);
                choices[0] = "";
                MultipleChoiceQuestionValidator::validateChoices(choices);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::CHOICES_CANNOT_BE_EMPTY, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateChoicesTest, should_throw_exception_when_choices_contains_at_least_one_very_long_choice) {
    EXPECT_THROW(
        {
            try {
                std::vector<std::string> choices(CHOICES);
                choices[0] = std::string(Enums::MAX_STRING_LENGTH + 1, 'a');
                MultipleChoiceQuestionValidator::validateChoices(choices);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::CHOICES_CANNOT_BE_VERY_LONG, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateChoicesTest, should_throw_exception_when_choices_contains_at_least_one_duplicate_choice) {
    EXPECT_THROW(
        {
            try {
                std::vector<std::string> choices(CHOICES);
                choices[0] = CHOICES[1];
                MultipleChoiceQuestionValidator::validateChoices(choices);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::CHOICES_CANNOT_HAVE_DUPLICATES, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateChoicesTest, should_return_the_choices_when_choices_are_valid) {
    auto choices = MultipleChoiceQuestionValidator::validateChoices(CHOICES);
    ASSERT_THAT(choices, testing::ElementsAreArray(CHOICES));
}
