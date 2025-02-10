#include "multiple_choice_answer.builder.h"

// Static const variables
static const uint8_t text = 1;
static const double degree = 0.5;

TEST(DefaultBuilderTest, given_multiple_choice_answer_builder_with_default_values) {
    auto answer = MultipleChoiceAnswerBuilder::create().build();

    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
}

TEST(SetTextTest, given_multiple_choice_answer_builder_with_text) {
    auto answer = MultipleChoiceAnswerBuilder::create().setText(text).build();

    EXPECT_EQ(answer->getText(), text);
    EXPECT_FALSE(answer->getDegree().has_value());
}

TEST(SetDegreeTest, given_multiple_choice_answer_builder_with_degree) {
    auto answer = MultipleChoiceAnswerBuilder::create().setDegree(degree).build();

    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_EQ(answer->getDegree(), degree);
}

TEST(SetTextAndDegreeTest, given_multiple_choice_answer_builder_with_custom_values) {
    auto answer = MultipleChoiceAnswerBuilder::create().setText(text).setDegree(degree).build();

    EXPECT_EQ(answer->getText(), text);
    EXPECT_EQ(answer->getDegree(), degree);
}
