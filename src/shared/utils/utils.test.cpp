#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <constants/enums.h>
#include <constants/messages.h>
#include <constants/test_defaults.h>
#include <utils/utils.h>

using namespace Enums;
using namespace TestDefaults;

TEST(GetAppRunModeTest, given_no_argv_then_returns_normal) {
    int argc = 1;
    char* argv[1] = {};

    EXPECT_EQ(RunMode::NORMAL, Utils::getAppRunMode(argc, argv));
}

TEST(GetAppRunModeTest, given_argv_with_test_then_returns_test) {
    int argc = 2;
    char* argv[2] = {const_cast<char*>(""), const_cast<char*>("test")};

    EXPECT_EQ(RunMode::TEST, Utils::getAppRunMode(argc, argv));
}

TEST(GetAppRunModeTest, given_argv_with_generate_questions_then_returns_generate_questions) {
    int argc = 2;
    char* argv[2] = {const_cast<char*>(""), const_cast<char*>("generate_questions")};

    EXPECT_EQ(RunMode::GENERATE_QUESTIONS, Utils::getAppRunMode(argc, argv));
}

TEST(GetAppRunModeTest, given_argv_with_invalid_mode_then_returns_normal) {
    int argc = 2;
    char* argv[2] = {const_cast<char*>(""), const_cast<char*>("any other mode")};

    EXPECT_EQ(RunMode::NORMAL, Utils::getAppRunMode(argc, argv));
}

TEST(SplitTest, given_string_with_defalt_delimiter_then_returns_vector_of_strings) {
    std::string input = R"(A
B
C)";
    std::vector<std::string> expected = {"A", "B", "C"};
    auto output = Utils::split(input);

    ASSERT_THAT(output, testing::ElementsAreArray(expected));
}

TEST(SplitTest, given_string_with_custom_delimiter_then_returns_vector_of_one_string) {
    std::string input = "A,B,C";
    std::vector<std::string> expected = {"A,B,C"};
    auto output = Utils::split(input, ' ');

    ASSERT_THAT(output, testing::ElementsAreArray(expected));
}

TEST(SplitTest, given_string_with_custom_delimiter_then_returns_vector_of_strings) {
    std::string input = "A,B,C";
    std::vector<std::string> expected = {"A", "B", "C"};
    auto output = Utils::split(input, ',');

    ASSERT_THAT(output, testing::ElementsAreArray(expected));
}

TEST(AskQuestionTest, given_no_vaild_answers_then_no_validation_needed_case_insensitive) {
    std::vector<std::string> validAnswers = {};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, ESSAY_ANSWER_1_UPPERCASE,
                                      ESSAY_QUESTION_1, validAnswers, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, ESSAY_ANSWER_1_LOWERCASE);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(ESSAY_QUESTION_1));
}

TEST(AskQuestionTest, given_no_vaild_answers_then_no_validation_needed_case_sensitive) {
    std::vector<std::string> validAnswers = {};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, ESSAY_ANSWER_1_UPPERCASE,
                                      ESSAY_QUESTION_1, validAnswers, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, ESSAY_ANSWER_1_UPPERCASE);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(ESSAY_QUESTION_1));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_insensitive) {
    std::string input = "YES";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, BOOL_QUESTION_1,
                                      BOOL_QUESTION_VALID_ANSWERS_WORDS, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, BOOL_QUESTION_VALID_ANSWERS_WORDS[0]);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(BOOL_QUESTION_1));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_sensitive) {
    std::string input = "yes";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, BOOL_QUESTION_1,
                                      BOOL_QUESTION_VALID_ANSWERS_WORDS, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, BOOL_QUESTION_VALID_ANSWERS_WORDS[0]);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(BOOL_QUESTION_1));
}

TEST(AskQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_with_white_space_immediately_will_be_trimmed_case_sensitive) {
    std::string input = "      yes                ";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, BOOL_QUESTION_1,
                                      BOOL_QUESTION_VALID_ANSWERS_WORDS, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, BOOL_QUESTION_VALID_ANSWERS_WORDS[0]);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(BOOL_QUESTION_1));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_from_2nd_trial_case_insensitive) {
    std::string input = "True\nYes";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, BOOL_QUESTION_1,
                                      BOOL_QUESTION_VALID_ANSWERS_WORDS, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, BOOL_QUESTION_VALID_ANSWERS_WORDS[0]);
    EXPECT_EQ(consoleOutputSplitted.size(), 4);
    EXPECT_EQ(consoleOutputSplitted[0], BOOL_QUESTION_1);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [yes, no]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case insensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], BOOL_QUESTION_1);
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_from_3rd_trial_case_sensitive) {
    std::string input = "yes\ntrue\nTrue";
    std::vector<std::string> validAnswers = {"True", "False"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, BOOL_QUESTION_1, validAnswers, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, "True");
    EXPECT_EQ(consoleOutputSplitted.size(), 7);
    EXPECT_EQ(consoleOutputSplitted[0], BOOL_QUESTION_1);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], BOOL_QUESTION_1);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[5], "");
    EXPECT_EQ(consoleOutputSplitted[6], BOOL_QUESTION_1);
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_immediately_case_insensitive_and_returns_true) {
    std::string input = "Y";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, BOOL_QUESTION_1,
                                      BOOL_QUESTION_VALID_ANSWERS, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, true);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(BOOL_QUESTION_1));
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_with_white_space_immediately_case_insensitive_and_returns_false) {
    std::string input = "   NO   ";
    std::vector<std::string> validAnswers = {"YES", "NO"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, BOOL_QUESTION_1, validAnswers, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, false);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(BOOL_QUESTION_1));
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_from_2nd_trial_case_insensitive_and_returns_false) {
    std::string input = "FALSE\nNO";
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, BOOL_QUESTION_1,
                                      BOOL_QUESTION_VALID_ANSWERS_WORDS, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, false);
    EXPECT_EQ(consoleOutputSplitted.size(), 4);
    EXPECT_EQ(consoleOutputSplitted[0], BOOL_QUESTION_1);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [yes, no]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case insensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], BOOL_QUESTION_1);
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_from_3rd_trial_case_sensitive_and_returns_true) {
    std::string input = "yes\ntrue\nTrue";
    std::vector<std::string> validAnswers = {"True", "False"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, BOOL_QUESTION_1, validAnswers, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, true);
    EXPECT_EQ(consoleOutputSplitted.size(), 7);
    EXPECT_EQ(consoleOutputSplitted[0], BOOL_QUESTION_1);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], BOOL_QUESTION_1);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[5], "");
    EXPECT_EQ(consoleOutputSplitted[6], BOOL_QUESTION_1);
}

TEST(ConvertIndexToCharTest, given_index_0_then_returns_A) {
    char output = Utils::convertIndexToChoiceChar(0);
    EXPECT_EQ(output, 'A');
}

TEST(ConvertIndexToCharTest, given_index_4_then_returns_E) {
    char output = Utils::convertIndexToChoiceChar(4);
    EXPECT_EQ(output, 'E');
}

TEST(ConvertIndexToCharTest, given_invalid_index_greater_than_25_then_throws_invalid_argument_exception) {
    EXPECT_THROW(
        {
            try {
                Utils::convertIndexToChoiceChar(26);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Invalid index, must be between 0 and 25", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ConvertChoiceCharToIndexTest, given_A_then_returns_0) {
    uint8_t output = Utils::convertChoiceCharToIndex('A');
    EXPECT_EQ(output, 0);
}

TEST(ConvertChoiceCharToIndexTest, given_E_then_returns_4) {
    uint8_t output = Utils::convertChoiceCharToIndex('E');
    EXPECT_EQ(output, 4);
}

TEST(ConvertChoiceCharToIndexTest, given_r_then_returns_17) {
    uint8_t output = Utils::convertChoiceCharToIndex('r');
    EXPECT_EQ(output, 17);
}

TEST(ConvertChoiceCharToIndexTest, given_z_then_returns_25) {
    uint8_t output = Utils::convertChoiceCharToIndex('z');
    EXPECT_EQ(output, 25);
}

TEST(ConvertChoiceCharToIndexTest,
     given_number_instead_of_alphabet_char_then_throws_invalid_argument_exception) {
    EXPECT_THROW(
        {
            try {
                Utils::convertChoiceCharToIndex('2');
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_CHOICE_CHAR, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ConvertChoiceCharToIndexTest,
     given_special_character_instead_of_alphabet_char_then_throws_invalid_argument_exception) {
    EXPECT_THROW(
        {
            try {
                Utils::convertChoiceCharToIndex('@');
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_CHOICE_CHAR, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(GenerateIndicesTest, given_a_size_of_zero_then_throws_invalid_argument_exception) {
    EXPECT_THROW(
        {
            try {
                unsigned short size = 0;
                Utils::generateIndices(size);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::SIZE_GT_ZERO, ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(GenerateIndicesTest, given_a_size_of_five_and_without_shuffling_then_returns_a_vector_of_sorted_indices) {
    std::vector<unsigned short> indices = Utils::generateIndices(5);
    std::vector<unsigned short> expected = {0, 1, 2, 3, 4};

    ASSERT_EQ(indices.size(), expected.size());
    ASSERT_THAT(indices, testing::ElementsAreArray(expected));
    EXPECT_EQ(indices, expected);
}

TEST(GenerateIndicesTest, given_a_size_of_one_and_with_shuffling_then_returns_the_same_indices) {
    std::vector<unsigned short> indices = Utils::generateIndices(1, true);

    ASSERT_EQ(indices.size(), 1);
    ASSERT_THAT(indices, testing::ElementsAre(0));
}

TEST(GenerateIndicesTest, given_a_size_of_five_and_with_shuffling_then_returns_a_vector_of_shuffled_indices) {
    std::vector<unsigned short> shuffledIndices = Utils::generateIndices(5, true);
    std::vector<unsigned short> sortedIndices = {0, 1, 2, 3, 4};

    ASSERT_EQ(shuffledIndices.size(), sortedIndices.size());
    ASSERT_THAT(shuffledIndices, testing::UnorderedElementsAreArray(sortedIndices));
    EXPECT_NE(shuffledIndices, sortedIndices);
}
