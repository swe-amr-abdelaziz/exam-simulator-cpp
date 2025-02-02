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

