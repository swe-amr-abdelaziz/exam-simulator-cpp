#include "multiple_choice_question.builder.h"

// Static const variables
static const std::string text = "What is the capital of the United States?";
static const uint8_t text1 = 1;
static const double degree1 = 0.5;
static const uint8_t text2 = 2;
static const double degree2 = 1.5;
static const std::vector<std::string> choices = {"A", "B", "C", "D"};

TEST(DefaultBuilderTest, given_multiple_choice_question_builder_with_default_values) {
    auto question = MultipleChoiceQuestionBuilder::create().build();

    EXPECT_EQ(question->getText(), TestDefaults::MCQ_TEXT);
    EXPECT_FALSE(question->getCorrectAnswer()->getText().has_value());
    EXPECT_FALSE(question->getCorrectAnswer()->getDegree().has_value());
    EXPECT_FALSE(question->getStudentAnswer()->getText().has_value());
    EXPECT_FALSE(question->getStudentAnswer()->getDegree().has_value());
    EXPECT_EQ(question->getChoices(), TestDefaults::CHOICES);
}

TEST(SetTextTest, given_multiple_choice_question_builder_with_text) {
    auto question = MultipleChoiceQuestionBuilder::create().setText(text).build();

    EXPECT_EQ(question->getText(), text);
}

TEST(SetCorrectAnswerTest, given_multiple_choice_question_builder_with_correct_answer) {
    auto correctAnswer = MultipleChoiceAnswerBuilder::create().setText(text1).setDegree(degree1).build();
    auto question =
        MultipleChoiceQuestionBuilder::create().setCorrectAnswer(std::move(correctAnswer)).build();

    EXPECT_EQ(question->getCorrectAnswer()->getText(), text1);
    EXPECT_EQ(question->getCorrectAnswer()->getDegree(), degree1);
}

TEST(SetStudentAnswerTest, given_multiple_choice_question_builder_with_student_answer) {
    auto studentAnswer = MultipleChoiceAnswerBuilder::create().setText(text2).setDegree(degree2).build();
    auto question =
        MultipleChoiceQuestionBuilder::create().setStudentAnswer(std::move(studentAnswer)).build();

    EXPECT_EQ(question->getStudentAnswer()->getText(), text2);
    EXPECT_EQ(question->getStudentAnswer()->getDegree(), degree2);
}

TEST(SetChoicesTest, given_multiple_choice_question_builder_with_choices) {
    auto question = MultipleChoiceQuestionBuilder::create().setChoices(choices).build();

    EXPECT_THAT(question->getChoices(), ::testing::ElementsAreArray(choices));
}

TEST(SetMixedValuesTest, given_multiple_choice_question_builder_with_mixed_values) {
    auto correctAnswer = MultipleChoiceAnswerBuilder::create().setText(text1).setDegree(degree1).build();
    auto studentAnswer = MultipleChoiceAnswerBuilder::create().setText(text2).setDegree(degree2).build();
    auto question = MultipleChoiceQuestionBuilder::create()
                        .setText(text)
                        .setCorrectAnswer(std::move(correctAnswer))
                        .setStudentAnswer(std::move(studentAnswer))
                        .setChoices(choices)
                        .build();

    EXPECT_EQ(question->getText(), text);
    EXPECT_EQ(question->getCorrectAnswer()->getText(), text1);
    EXPECT_EQ(question->getCorrectAnswer()->getDegree(), degree1);
    EXPECT_EQ(question->getStudentAnswer()->getText(), text2);
    EXPECT_EQ(question->getStudentAnswer()->getDegree(), degree2);
    EXPECT_THAT(question->getChoices(), ::testing::ElementsAreArray(choices));
}
