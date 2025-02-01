#ifndef ENUMS_H
#define ENUMS_H

#include <map>
#include <string>

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

#endif // ENUMS_H
