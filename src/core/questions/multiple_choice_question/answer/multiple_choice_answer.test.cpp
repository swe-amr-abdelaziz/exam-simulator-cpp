#include "multiple_choice_answer.h"

TEST(MultipleChoiceAnswerDefaultValuesTest, initialize_multiple_choice_answer_with_no_text_and_no_degree) {
    auto answer = std::make_unique<MultipleChoiceAnswer>();

    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), std::nullopt);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(GetTextTest, given_multiple_choice_answer_with_valid_text_then_text_is_returned) {
    uint8_t text = 1;
    auto answer = std::make_unique<MultipleChoiceAnswer>(text);

    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_EQ(answer->getText(), text);
}

TEST(SetTextTest, given_multiple_choice_answer_with_valid_text_then_text_is_set) {
    uint8_t text1 = 1;
    auto answer = std::make_unique<MultipleChoiceAnswer>(text1);
    uint8_t text2 = 2;
    answer->setText(text2);

    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_EQ(answer->getText(), text2);
}

TEST(GetDegreeTest, given_multiple_choice_answer_with_valid_degree_then_degree_is_returned) {
    uint8_t text = 1;
    double degree = 5.0;
    auto answer = std::make_unique<MultipleChoiceAnswer>(text, degree);

    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getDegree(), degree);
}

TEST(SetDegreeTest, given_multiple_choice_answer_with_valid_degree_then_degree_is_set) {
    uint8_t text = 1;
    double degree1 = 5.0;
    auto answer = std::make_unique<MultipleChoiceAnswer>(text, degree1);
    double degree2 = 8.0;
    answer->setDegree(degree2);

    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getDegree(), degree2);
}
