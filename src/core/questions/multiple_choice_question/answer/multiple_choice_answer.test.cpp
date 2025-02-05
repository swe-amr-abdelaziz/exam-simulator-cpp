#include "../answer/multiple_choice_answer.h"

static std::vector<std::string> choices = {"Apple", "Orange", "Banana"};

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_choices) {
    std::vector<std::string> myChoices = {"Apple", "Orange", "Banana", "Mango"};
    std::unique_ptr<MultipleChoiceAnswer> answer = std::make_unique<MultipleChoiceAnswer>(myChoices);
    ASSERT_THAT(answer->getChoices(), testing::ElementsAre("Apple", "Orange", "Banana", "Mango"));
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_invalid_choices_less_than_2) {
    std::vector<std::string> invalidChoices = {"Apple", "Orange"};
    EXPECT_THROW(
        {
            try {
                std::unique_ptr<MultipleChoiceAnswer> answer =
                    std::make_unique<MultipleChoiceAnswer>(invalidChoices);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Choices must be between 3 and 5 elements", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_invalid_choices_more_than_5) {
    std::vector<std::string> invalidChoices = {"Apple", "Orange",     "Banana",
                                               "Mango", "Strawberry", "Grape"};
    EXPECT_THROW(
        {
            try {
                std::unique_ptr<MultipleChoiceAnswer> answer =
                    std::make_unique<MultipleChoiceAnswer>(invalidChoices);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Choices must be between 3 and 5 elements", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_no_text_and_no_degree) {
    std::unique_ptr<MultipleChoiceAnswer> answer = std::make_unique<MultipleChoiceAnswer>(choices);
    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), std::nullopt);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_choice_text_and_no_degree) {
    std::unique_ptr<MultipleChoiceAnswer> answer = std::make_unique<MultipleChoiceAnswer>(choices, 0);
    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), 0);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_invalid_choice_text_and_no_degree) {
    EXPECT_THROW(
        {
            try {
                std::unique_ptr<MultipleChoiceAnswer> answer =
                    std::make_unique<MultipleChoiceAnswer>(choices, 3);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Answer text must be one of the provided choices", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_text_and_valid_degree) {
    std::unique_ptr<MultipleChoiceAnswer> answer = std::make_unique<MultipleChoiceAnswer>(choices, 1, 5);
    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), 1);
    EXPECT_EQ(answer->getDegree(), 5.0);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_text_and_invalid_degree) {
    EXPECT_THROW(
        {
            try {
                std::unique_ptr<MultipleChoiceAnswer> answer =
                    std::make_unique<MultipleChoiceAnswer>(choices, 1, -1);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Degree must be greater than or equal to zero", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, set_valid_choice_text_for_multiple_choice_answer) {
    std::unique_ptr<MultipleChoiceAnswer> answer = std::make_unique<MultipleChoiceAnswer>(choices);
    answer->setText(2);
    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), 2);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(MultipleChoiceAnswerTest, set_invalid_choice_text_for_multiple_choice_answer) {
    EXPECT_THROW(
        {
            try {
                std::unique_ptr<MultipleChoiceAnswer> answer =
                    std::make_unique<MultipleChoiceAnswer>(choices);
                answer->setText(5);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Answer text must be one of the provided choices", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, set_valid_degree_for_multiple_choice_answer) {
    std::unique_ptr<MultipleChoiceAnswer> answer = std::make_unique<MultipleChoiceAnswer>(choices);
    answer->setDegree(5);
    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), std::nullopt);
    EXPECT_EQ(answer->getDegree(), 5.0);
}

TEST(MultipleChoiceAnswerTest, set_invalid_degree_for_multiple_choice_answer) {
    EXPECT_THROW(
        {
            try {
                std::unique_ptr<MultipleChoiceAnswer> answer =
                    std::make_unique<MultipleChoiceAnswer>(choices);
                answer->setDegree(-10);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Degree must be greater than or equal to zero", ex.what());
                throw;
            }
        },
        std::exception);
}
