#include "utils.h"

TEST(GetAppRunModeTest, given_no_argv_then_returns_normal) {
    int argc = 1;
    char* argv[1] = {};
    EXPECT_EQ(RunMode::NORMAL, Utils::getAppRunMode(argc, argv));
}

TEST(GetAppRunModeTest, given_argv_with_test_then_returns_test) {
    int argc = 2;
    char* argv[2] = {(char*) "", (char*) "test"};
    EXPECT_EQ(RunMode::TEST, Utils::getAppRunMode(argc, argv));
}

TEST(GetAppRunModeTest, given_argv_with_generate_questions_then_returns_generate_questions) {
    int argc = 2;
    char* argv[2] = {(char*) "", (char*) "generate_questions"};
    EXPECT_EQ(RunMode::GENERATE_QUESTIONS, Utils::getAppRunMode(argc, argv));
}

TEST(GetAppRunModeTest, given_argv_with_invalid_mode_then_returns_normal) {
    int argc = 2;
    char* argv[2] = {(char*) "", (char*) "any other mode"};
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
    std::string input = "I AM FINE, THANKS";
    std::string prompt = "How are you?";
    std::vector<std::string> validAnswers = {};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, prompt, validAnswers, false);
    EXPECT_EQ(funcOutput, "i am fine, thanks");
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_no_vaild_answers_then_no_validation_needed_case_sensitive) {
    std::string input = "I AM FINE, THANKS";
    std::string prompt = "How are you?";
    std::vector<std::string> validAnswers = {};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(funcOutput, "I AM FINE, THANKS");
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_insensitive) {
    std::string input = "YES";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, prompt, validAnswers, false);
    EXPECT_EQ(funcOutput, "yes");
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_sensitive) {
    std::string input = "yes";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(funcOutput, "yes");
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_with_white_space_immediately_will_be_trimmed_case_sensitive) {
    std::string input = "      yes                ";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(funcOutput, "yes");
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_from_2nd_trial_case_insensitive) {
    std::string input = "True\nYes";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, prompt, validAnswers, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, "yes");
    EXPECT_EQ(consoleOutputSplitted.size(), 4);
    EXPECT_EQ(consoleOutputSplitted[0], prompt);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [yes, no]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case insensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], prompt);
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_from_3rd_trial_case_sensitive) {
    std::string input = "yes\ntrue\nTrue";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"True", "False"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askQuestion, input, prompt, validAnswers, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, "True");
    EXPECT_EQ(consoleOutputSplitted.size(), 7);
    EXPECT_EQ(consoleOutputSplitted[0], prompt);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], prompt);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[5], "");
    EXPECT_EQ(consoleOutputSplitted[6], prompt);
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_immediately_case_insensitive_and_returns_true) {
    std::string input = "Y";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"y", "n"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, prompt, validAnswers, false);
    EXPECT_EQ(funcOutput, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(prompt));
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_with_white_space_immediately_case_insensitive_and_returns_false) {
    std::string input = "   NO   ";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"YES", "NO"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(funcOutput, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);
    ASSERT_THAT(consoleOutputSplitted, testing::ElementsAre(prompt));
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_from_2nd_trial_case_insensitive_and_returns_false) {
    std::string input = "FALSE\nNO";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, prompt, validAnswers, false);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, false);
    EXPECT_EQ(consoleOutputSplitted.size(), 4);
    EXPECT_EQ(consoleOutputSplitted[0], prompt);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [yes, no]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case insensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], prompt);
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_from_3rd_trial_case_sensitive_and_returns_true) {
    std::string input = "yes\ntrue\nTrue";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"True", "False"};
    auto [funcOutput, consoleOutput] =
        Utils::invokeAndCaptureOutput(Utils::askBoolQuestion, input, prompt, validAnswers, true);
    std::vector<std::string> consoleOutputSplitted = Utils::split(consoleOutput);

    EXPECT_EQ(funcOutput, true);
    EXPECT_EQ(consoleOutputSplitted.size(), 7);
    EXPECT_EQ(consoleOutputSplitted[0], prompt);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[2], "");
    EXPECT_EQ(consoleOutputSplitted[3], prompt);

    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutputSplitted[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutputSplitted[5], "");
    EXPECT_EQ(consoleOutputSplitted[6], prompt);
}

TEST(ConvertIndexToCharTest, given_index_0_then_returns_A) {
    char output = Utils::convertIndexToChoiceChar(0);
    EXPECT_EQ(output, 'A');
}

TEST(ConvertIndexToCharTest, given_index_4_then_returns_E) {
    char output = Utils::convertIndexToChoiceChar(4);
    EXPECT_EQ(output, 'E');
}

TEST(ConvertIndexToCharTest, given_invalid_index_less_than_zero_then_throws_invalid_argument) {
    EXPECT_THROW(
        {
            try {
                Utils::convertIndexToChoiceChar(-1);
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Invalid index, must be between 0 and 25", ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ConvertIndexToCharTest, given_invalid_index_greater_than_25_then_throws_invalid_argument) {
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
    int output = Utils::convertChoiceCharToIndex('A');
    EXPECT_EQ(output, 0);
}

TEST(ConvertChoiceCharToIndexTest, given_E_then_returns_4) {
    int output = Utils::convertChoiceCharToIndex('E');
    EXPECT_EQ(output, 4);
}

TEST(ConvertChoiceCharToIndexTest, given_r_then_returns_17) {
    int output = Utils::convertChoiceCharToIndex('r');
    EXPECT_EQ(output, 17);
}

TEST(ConvertChoiceCharToIndexTest, given_z_then_returns_25) {
    int output = Utils::convertChoiceCharToIndex('z');
    EXPECT_EQ(output, 25);
}

TEST(ConvertChoiceCharToIndexTest, given_number_instead_of_alphabet_char_then_throws_invalid_argument) {
    EXPECT_THROW(
        {
            try {
                Utils::convertChoiceCharToIndex('2');
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Invalid choice character, must be between A and Z (case insensitive)",
                             ex.what());
                throw;
            }
        },
        std::exception);
}

TEST(ConvertChoiceCharToIndexTest,
     given_special_character_instead_of_alphabet_char_then_throws_invalid_argument) {
    EXPECT_THROW(
        {
            try {
                Utils::convertChoiceCharToIndex('@');
            } catch (const std::exception& ex) {
                EXPECT_STREQ("Invalid choice character, must be between A and Z (case insensitive)",
                             ex.what());
                throw;
            }
        },
        std::exception);
}
