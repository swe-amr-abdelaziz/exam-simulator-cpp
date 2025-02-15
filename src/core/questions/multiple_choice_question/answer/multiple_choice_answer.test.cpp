#include <gtest/gtest.h>

#include <multiple_choice_question/answer/multiple_choice_answer.h>

TEST(MultipleChoiceAnswerDefaultValuesTest, initialize_multiple_choice_answer_with_no_value_and_no_degree) {
    auto answer = std::make_unique<MultipleChoiceAnswer>();

    EXPECT_FALSE(answer->getValue().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getValue(), std::nullopt);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(GetValueTest, given_multiple_choice_answer_with_valid_value_then_value_is_returned) {
    uint8_t value = 1;
    auto answer = std::make_unique<MultipleChoiceAnswer>(value);

    EXPECT_TRUE(answer->getValue().has_value());
    EXPECT_EQ(answer->getValue(), value);
}

TEST(SetValueTest, given_multiple_choice_answer_with_valid_value_then_value_is_set) {
    uint8_t value1 = 1;
    auto answer = std::make_unique<MultipleChoiceAnswer>(value1);
    uint8_t value2 = 2;
    answer->setValue(value2);

    EXPECT_TRUE(answer->getValue().has_value());
    EXPECT_EQ(answer->getValue(), value2);
}

TEST(GetDegreeTest, given_multiple_choice_answer_with_valid_degree_then_degree_is_returned) {
    uint8_t value = 1;
    double degree = 5.0;
    auto answer = std::make_unique<MultipleChoiceAnswer>(value, degree);

    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getDegree(), degree);
}

TEST(SetDegreeTest, given_multiple_choice_answer_with_valid_degree_then_degree_is_set) {
    uint8_t value = 1;
    double degree1 = 5.0;
    auto answer = std::make_unique<MultipleChoiceAnswer>(value, degree1);
    double degree2 = 8.0;
    answer->setDegree(degree2);

    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getDegree(), degree2);
}

TEST(CloneTest,
     given_multiple_choice_answer_with_valid_value_and_degree_then_clone_is_created_and_values_are_copied) {
    uint8_t valueOriginal = 1;
    double degreeOriginal = 5.0;
    auto origin = std::make_unique<MultipleChoiceAnswer>(valueOriginal, degreeOriginal);
    auto clone = origin->clone();

    uint8_t valueClone = 2;
    double degreeClone = 8.0;
    clone->setValue(valueClone);
    clone->setDegree(degreeClone);

    EXPECT_EQ(origin->getValue(), valueOriginal);
    EXPECT_EQ(clone->getValue(), valueClone);
    EXPECT_EQ(origin->getDegree(), degreeOriginal);
    EXPECT_EQ(clone->getDegree(), degreeClone);
}
