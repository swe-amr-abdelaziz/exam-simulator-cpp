#ifndef TEST_DEFAULTS_H
#define TEST_DEFAULTS_H

#include <cstdint>
#include <string>
#include <vector>

namespace TestDefaults {

const std::string ESSAY_ANSWER_1_LOWERCASE = "i am fine, thanks";
const std::string ESSAY_ANSWER_1_UPPERCASE = "I AM FINE, THANKS";
const std::string ESSAY_QUESTION_1 = "How are you?";
const std::string BOOL_QUESTION_1 = "Are you a software engineer?";
const std::vector<std::string> BOOL_QUESTION_VALID_ANSWERS_WORDS = {"yes", "no"};
const std::string MCQ_TEXT = "What is the name of the first month of the year?";
const std::vector<std::string> CHOICES = {"January", "February", "March", "April", "May"};
const uint8_t MCQ_CORRECT_ANSWER_TEXT = 0;
const double MCQ_CORRECT_ANSWER_DEGREE = 1.0;

} // namespace TestDefaults

#endif // TEST_DEFAULTS_H
