#include "utils.h"

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
    EXPECT_EQ(output.size(), expected.size());
    for (size_t i = 0; i < output.size(); i++) {
        EXPECT_EQ(output[i], expected[i]);
    }
}

TEST(SplitTest, given_string_with_custom_delimiter_then_returns_vector_of_one_string) {
    std::string input = "A,B,C";
    std::vector<std::string> expected = {"A,B,C"};
    auto output = Utils::split(input, ' ');
    EXPECT_EQ(output.size(), expected.size());
    for (size_t i = 0; i < output.size(); i++) {
        EXPECT_EQ(output[i], expected[i]);
    }
}

TEST(SplitTest, given_string_with_custom_delimiter_then_returns_vector_of_strings) {
    std::string input = "A,B,C";
    std::vector<std::string> expected = {"A", "B", "C"};
    auto output = Utils::split(input, ',');
    EXPECT_EQ(output.size(), expected.size());
    for (size_t i = 0; i < output.size(); i++) {
        EXPECT_EQ(output[i], expected[i]);
    }
}

TEST(AskQuestionTest, given_no_vaild_answers_then_no_validation_needed_case_insensitive) {
    std::string input = "I AM FINE, THANKS";
    std::string prompt = "How are you?";
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, {}, false);
    EXPECT_EQ(std::get<0>(tuple), "i am fine, thanks");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    EXPECT_EQ(consoleOutput[0], prompt);
}

TEST(AskQuestionTest, given_no_vaild_answers_then_no_validation_needed_case_sensitive) {
    std::string input = "I AM FINE, THANKS";
    std::string prompt = "How are you?";
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, {}, true);
    EXPECT_EQ(std::get<0>(tuple), "I AM FINE, THANKS");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    EXPECT_EQ(consoleOutput[0], prompt);
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_insensitive) {
    std::string input = "YES";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, validAnswers, false);
    EXPECT_EQ(std::get<0>(tuple), "yes");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    EXPECT_EQ(consoleOutput[0], prompt);
}

TEST(AskQuestionTest, given_vaild_answers_then_enters_a_valid_answer_immediately_case_sensitive) {
    std::string input = "yes";
    std::string prompt = "Are you a software engineer?";
    std::vector<std::string> validAnswers = {"yes", "no"};
    std::tuple<std::string, std::string> tuple =
        getFunctionOutput<std::string>(Utils::askQuestion, input, prompt, validAnswers, true);
    EXPECT_EQ(std::get<0>(tuple), "yes");
    std::vector<std::string> consoleOutput = Utils::split(std::get<1>(tuple));
    EXPECT_EQ(consoleOutput[0], prompt);
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
    EXPECT_EQ(consoleOutput[0], prompt);
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

