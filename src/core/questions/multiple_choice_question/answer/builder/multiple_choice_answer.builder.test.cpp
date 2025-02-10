#include "multiple_choice_answer.builder.h"

// Static const variables
static const uint8_t value = 1;
static const double degree = 0.5;

TEST(DefaultBuilderTest, given_multiple_choice_answer_builder_with_default_values) {
    auto answer = MultipleChoiceAnswerBuilder::create().build();

    EXPECT_FALSE(answer->getValue().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
}

TEST(SetValueTest, given_multiple_choice_answer_builder_with_value) {
    auto answer = MultipleChoiceAnswerBuilder::create().setValue(value).build();

    EXPECT_EQ(answer->getValue(), value);
    EXPECT_FALSE(answer->getDegree().has_value());
}

TEST(SetDegreeTest, given_multiple_choice_answer_builder_with_degree) {
    auto answer = MultipleChoiceAnswerBuilder::create().setDegree(degree).build();

    EXPECT_FALSE(answer->getValue().has_value());
    EXPECT_EQ(answer->getDegree(), degree);
}

TEST(SetValueAndDegreeTest, given_multiple_choice_answer_builder_with_custom_values) {
    auto answer = MultipleChoiceAnswerBuilder::create().setValue(value).setDegree(degree).build();

    EXPECT_EQ(answer->getValue(), value);
    EXPECT_EQ(answer->getDegree(), degree);
}
