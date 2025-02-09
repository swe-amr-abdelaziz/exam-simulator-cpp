#ifndef UTILS_H
#define UTILS_H

#include "../constants/enums.h"
#include "utils.template.cpp"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
using namespace Enums;

class Utils {
public:
    static RunMode getAppRunMode(const int& argc, char* argv[]);
    static std::string askQuestion(const std::string& question,
                                   const std::vector<std::string>& validAnswers = {},
                                   bool caseSensitive = false);
    static bool askBoolQuestion(const std::string& question,
                                const std::vector<std::string>& validAnswers = {"y", "n"},
                                bool caseSensitive = false);
    static std::vector<std::string> split(std::string str, char delimiter = '\n');
    static char convertIndexToChoiceChar(uint8_t index);
    static uint8_t convertChoiceCharToIndex(char ch);
    static std::vector<unsigned short> generateIndices(const unsigned short& size,
                                                       const bool& shuffle = false);

    template <typename F, typename... Args>
    static auto invokeAndCaptureOutput(F&& func, std::string input, Args&&... args) {
        return ::invokeAndCaptureOutput(std::forward<F>(func), input, std::forward<Args>(args)...);
    }

    template <typename Obj, typename Ret, typename... Args>
    static auto invokeAndCaptureOutput(Ret (Obj::*memFunc)(Args...), std::string input, Obj* obj,
                                       Args... args) {
        return ::invokeAndCaptureOutput(memFunc, input, obj, std::forward<Args>(args)...);
    }

private:
    static std::string printAnswersArray(const std::vector<std::string>& validAnswers);
    static std::string toLower(const std::string& str);
    static std::string trim(const std::string& str);
    static std::string formailzeAnswer(const std::string& answer, const bool& caseSensitive);
};

#endif // UTILS_H
