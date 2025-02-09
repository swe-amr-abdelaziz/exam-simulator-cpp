#include "../../../../../shared/constants/test_defaults.h"
#include "multiple_choice_answer.builder.h"

using namespace TestDefaults;

TEST(DefaultBuilderTest, given_multiple_choice_answer_builder_with_default_values) {
    auto answer = MultipleChoiceAnswerBuilder::create().build();

    ASSERT_THAT(answer->getChoices(), testing::ElementsAreArray(CHOICES));
    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
}

TEST(SetChoicesTest, given_multiple_choice_answer_builder_with_choices) {
    std::vector<std::string> subChoices(&CHOICES[0], &CHOICES[3]);
    auto answer = MultipleChoiceAnswerBuilder::create().setChoices(subChoices).build();

    ASSERT_THAT(answer->getChoices(), testing::ElementsAreArray(subChoices));
    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
}

TEST(SetTextTest, given_multiple_choice_answer_builder_with_text) {
    uint8_t text = 3;
    auto answer = MultipleChoiceAnswerBuilder::create().setText(text).build();

    EXPECT_EQ(answer->getText(), text);
    EXPECT_FALSE(answer->getDegree().has_value());
}

TEST(SetDegreeTest, given_multiple_choice_answer_builder_with_degree) {
    double degree = 0.5;
    auto answer = MultipleChoiceAnswerBuilder::create().setDegree(degree).build();

    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_EQ(answer->getDegree(), degree);
}

TEST(ResetTest, given_multiple_choice_answer_builder_with_custom_values) {
    uint8_t text = 1;
    double degree = 0.5;
    auto answer =
        MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).setText(text).setDegree(degree).build();

    ASSERT_THAT(answer->getChoices(), testing::ElementsAreArray(CHOICES));
    EXPECT_EQ(answer->getText(), text);
    EXPECT_EQ(answer->getDegree(), degree);
}
