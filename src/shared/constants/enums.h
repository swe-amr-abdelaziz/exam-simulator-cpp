#ifndef ENUMS_H
#define ENUMS_H

#include <map>
#include <string>
#include <vector>

namespace Enums {

enum RunMode {
    NORMAL,
    TEST,
    GENERATE_QUESTIONS,
};

const std::map<RunMode, std::string> RUN_MODES = {
    {RunMode::NORMAL, "normal"},
    {RunMode::TEST, "test"},
    {RunMode::GENERATE_QUESTIONS, "generate_questions"},
};

enum QuestionType {
    MCQ,
};

const std::vector<std::string> BOOL_QUESTION_VALID_ANSWERS = {"y", "n"};

const std::string WHITESPACES = " \t\n\r\f\v";

const int MAX_STRING_LENGTH = 500;

const int MIN_CHOICES = 3;

const int MAX_CHOICES = 5;

} // namespace Enums

#endif // ENUMS_H
