#include "utils.h"
#include "gmock/gmock.h"

template <typename T>
std::tuple<T, std::string>
    getFunctionOutput(T (*func)(const std::string& question,
                                const std::vector<std::string>& validAnswers, bool caseSensitive),
                      std::string input, std::string question,
                      std::vector<std::string> validAnswers, bool caseSensitive) {
    std::istringstream inputBuffer(input);
    std::streambuf* cinBuffer = std::cin.rdbuf(inputBuffer.rdbuf());
    testing::internal::CaptureStdout();
    T funcOutput = func(question, validAnswers, caseSensitive);
    std::cin.rdbuf(cinBuffer);
    std::string consoleOutput = testing::internal::GetCapturedStdout();
    return std::make_tuple(funcOutput, consoleOutput);
}

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
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, {}, false);
    EXPECT_EQ(std::get<0>(tuple), "i am fine, thanks");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    ASSERT_THAT(consoleOutput, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_no_vaild_answers_then_no_validation_needed_case_sensitive) {
    std::string input = "I AM FINE, THANKS";
    std::string prompt = "How are you?";
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, {}, true);
    EXPECT_EQ(std::get<0>(tuple), "I AM FINE, THANKS");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    ASSERT_THAT(consoleOutput, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_insensitive) {
    std::string input = "YES";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, validAnswers, false);
    EXPECT_EQ(std::get<0>(tuple), "yes");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    ASSERT_THAT(consoleOutput, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_sensitive) {
    std::string input = "yes";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(std::get<0>(tuple), "yes");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    ASSERT_THAT(consoleOutput, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_with_white_space_immediately_will_be_trimmed_case_sensitive) {
    std::string input = "      yes                ";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(std::get<0>(tuple), "yes");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    ASSERT_THAT(consoleOutput, testing::ElementsAre(prompt));
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_from_2nd_trial_case_insensitive) {
    std::string input = "True\nYes";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, validAnswers, false);
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));

    EXPECT_EQ(std::get<0>(tuple), "yes");
    EXPECT_EQ(consoleOutput.size(), 4);
    EXPECT_EQ(consoleOutput[0], prompt);

    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Please choose from: [yes, no]"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("case insensitive"));

    EXPECT_EQ(consoleOutput[2], "");
    EXPECT_EQ(consoleOutput[3], prompt);
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_from_3rd_trial_case_sensitive) {
    std::string input = "yes\ntrue\nTrue";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"True", "False"};
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, validAnswers, true);
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));

    EXPECT_EQ(std::get<0>(tuple), "True");
    EXPECT_EQ(consoleOutput.size(), 7);
    EXPECT_EQ(consoleOutput[0], prompt);

    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutput[2], "");
    EXPECT_EQ(consoleOutput[3], prompt);

    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutput[5], "");
    EXPECT_EQ(consoleOutput[6], prompt);
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_immediately_case_insensitive_and_returns_true) {
    std::string input = "Y";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"y", "n"};
    std::tuple<bool, std::string> tuple =
        getFunctionOutput<bool>(Utils::askBoolQuestion, input, prompt, validAnswers, false);
    EXPECT_EQ(std::get<0>(tuple), true);
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    ASSERT_THAT(consoleOutput, testing::ElementsAre(prompt));
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_with_white_space_immediately_case_insensitive_and_returns_false) {
    std::string input = "   NO   ";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"YES", "NO"};
    std::tuple<bool, std::string> tuple =
        getFunctionOutput<bool>(Utils::askBoolQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(std::get<0>(tuple), false);
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    ASSERT_THAT(consoleOutput, testing::ElementsAre(prompt));
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_from_2nd_trial_case_insensitive_and_returns_false) {
    std::string input = "FALSE\nNO";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    std::tuple<bool, std::string> tuple =
        getFunctionOutput<bool>(Utils::askBoolQuestion, input, prompt, validAnswers, false);
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));

    EXPECT_EQ(std::get<0>(tuple), false);
    EXPECT_EQ(consoleOutput.size(), 4);
    EXPECT_EQ(consoleOutput[0], prompt);

    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Please choose from: [yes, no]"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("case insensitive"));

    EXPECT_EQ(consoleOutput[2], "");
    EXPECT_EQ(consoleOutput[3], prompt);
}

TEST(AskBoolQuestionTest,
     given_vaild_answers_then_enters_a_valid_answer_from_3rd_trial_case_sensitive_and_returns_true) {
    std::string input = "yes\ntrue\nTrue";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"True", "False"};
    std::tuple<bool, std::string> tuple =
        getFunctionOutput<bool>(Utils::askBoolQuestion, input, prompt, validAnswers, true);
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));

    EXPECT_EQ(std::get<0>(tuple), true);
    EXPECT_EQ(consoleOutput.size(), 7);
    EXPECT_EQ(consoleOutput[0], prompt);

    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutput[2], "");
    EXPECT_EQ(consoleOutput[3], prompt);

    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Invalid answer"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("Please choose from: [True, False]"));
    EXPECT_THAT(consoleOutput[1], testing::HasSubstr("case sensitive"));

    EXPECT_EQ(consoleOutput[5], "");
    EXPECT_EQ(consoleOutput[6], prompt);
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
