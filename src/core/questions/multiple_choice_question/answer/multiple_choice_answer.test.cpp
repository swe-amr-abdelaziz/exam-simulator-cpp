#include "../../../../shared/constants/test_defaults.h"
#include "builder/multiple_choice_answer.builder.h"

using namespace TestDefaults;

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_choices) {
    std::vector<std::string> subChoices(&CHOICES[0], &CHOICES[4]);

    std::unique_ptr<MultipleChoiceAnswer> answer =
        MultipleChoiceAnswerBuilder::create().setChoices(subChoices).build();

    ASSERT_THAT(answer->getChoices(),
                testing::ElementsAre(CHOICES[0], CHOICES[1], CHOICES[2], CHOICES[3]));
}

TEST(MultipleChoiceAnswerTest, set_multiple_choice_answer_with_valid_choices) {
    std::vector<std::string> choices1(&CHOICES[0], &CHOICES[3]);
    std::vector<std::string> choices2(&CHOICES[0], &CHOICES[4]);

    auto answer = MultipleChoiceAnswerBuilder::create().setChoices(choices1).build();
    answer->setChoices(choices2);

    ASSERT_THAT(answer->getChoices(),
                testing::ElementsAre(CHOICES[0], CHOICES[1], CHOICES[2], CHOICES[3]));
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_invalid_choices_less_than_2) {
    std::vector<std::string> invalidChoices(&CHOICES[0], &CHOICES[1]);

    EXPECT_THROW(
        {
            try {
                auto answer = MultipleChoiceAnswerBuilder::create().build();
                answer->setChoices(invalidChoices);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Choices must be between 3 and 5 elements", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_invalid_choices_more_than_5) {
    std::vector<std::string> invalidChoices(&CHOICES[0], &CHOICES[5]);
    invalidChoices.push_back("dummy");

    EXPECT_THROW(
        {
            try {
                auto answer = MultipleChoiceAnswerBuilder::create().build();
                answer->setChoices(invalidChoices);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Choices must be between 3 and 5 elements", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_no_text_and_no_degree) {
    auto answer = MultipleChoiceAnswerBuilder::create().build();

    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), std::nullopt);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_choice_text_and_no_degree) {
    uint8_t text = 0;
    auto answer = MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).setText(text).build();

    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), text);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_invalid_choice_text_and_no_degree) {
    uint8_t text = 5;

    EXPECT_THROW(
        {
            try {
                auto answer =
                    MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).setText(text).build();
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Answer text must be one of the provided choices", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_text_and_valid_degree) {
    uint8_t text = 1;
    double degree = 5;
    auto answer =
        MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).setText(text).setDegree(degree).build();

    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), text);
    EXPECT_EQ(answer->getDegree(), degree);
}

TEST(MultipleChoiceAnswerTest, initialize_multiple_choice_answer_with_valid_text_and_invalid_degree) {
    uint8_t text = 1;
    double degree = -1;

    EXPECT_THROW(
        {
            try {
                auto answer = MultipleChoiceAnswerBuilder::create()
                                  .setChoices(CHOICES)
                                  .setText(text)
                                  .setDegree(degree)
                                  .build();
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Degree must be greater than or equal to zero", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, set_valid_choice_text_for_multiple_choice_answer) {
    auto answer = MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).build();
    uint8_t text = 2;
    answer->setText(text);

    EXPECT_TRUE(answer->getText().has_value());
    EXPECT_FALSE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), text);
    EXPECT_EQ(answer->getDegree(), std::nullopt);
}

TEST(MultipleChoiceAnswerTest, set_invalid_choice_text_for_multiple_choice_answer) {
    uint8_t text = 5;

    EXPECT_THROW(
        {
            try {
                auto answer = MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).build();
                answer->setText(text);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Answer text must be one of the provided choices", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(MultipleChoiceAnswerTest, set_valid_degree_for_multiple_choice_answer) {
    auto answer = MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).build();
    double degree = 5.0;
    answer->setDegree(degree);

    EXPECT_FALSE(answer->getText().has_value());
    EXPECT_TRUE(answer->getDegree().has_value());
    EXPECT_EQ(answer->getText(), std::nullopt);
    EXPECT_EQ(answer->getDegree(), degree);
}

TEST(MultipleChoiceAnswerTest, set_invalid_degree_for_multiple_choice_answer) {
    auto answer = MultipleChoiceAnswerBuilder::create().setChoices(CHOICES).build();
    double degree = -10.0;

    EXPECT_THROW(
        {
            try {
                answer->setDegree(degree);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Degree must be greater than or equal to zero", ex.what());
                throw;
            }
        },
        std::exception);
}
