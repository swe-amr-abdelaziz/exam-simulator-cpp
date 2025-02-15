#include <gtest/gtest.h>

#include <constants/messages.h>
#include <constants/test_defaults.h>
#include <multiple_choice_question/answer/validator/multiple_choice_answer.validator.h>
#include <utils/utils.h>

TEST(ValidateValueTest, should_throw_exception_when_value_index_is_greater_than_25) {
    EXPECT_THROW(
        {
            try {
                uint8_t value = Utils::convertChoiceCharToIndex('Z');
                value++;
                MultipleChoiceAnswerValidator::validateValue(value);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_CHAR_INDEX, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateValueTest, should_return_value_when_value_index_is_in_choices) {
    uint8_t value = static_cast<uint8_t>(TestDefaults::CHOICES.size() - 1);
    auto output = MultipleChoiceAnswerValidator::validateValue(value);
    EXPECT_EQ(output, value);
}

TEST(ValidateDegreeTest, should_throw_exception_when_degree_is_less_than_zero) {
    EXPECT_THROW(
        {
            try {
                double degree = -1;
                MultipleChoiceAnswerValidator::validateDergree(degree);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_DEGREE, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ValidateDegreeTest, should_return_degree_when_given_a_valid_degree) {
    double degree = 5.0;
    auto output = MultipleChoiceAnswerValidator::validateDergree(degree);
    EXPECT_EQ(output, degree);
}
