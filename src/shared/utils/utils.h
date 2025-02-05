#ifndef UTILS_H
#define UTILS_H

#include "../enums/enums.h"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
    static char convertIndexToChoiceChar(int index);
    static int convertChoiceCharToIndex(char ch);

    template <typename F, typename... Args>
    static auto invokeAndCaptureOutput(F&& func, std::string input, Args&&... args) {
        // Detect the return type of the function
        using Ret = std::invoke_result_t<F, Args...>;
        Ret funcOutput;

        // Simulate the user input
        std::istringstream inputBuffer(input);
        std::streambuf* cinBuffer = std::cin.rdbuf(inputBuffer.rdbuf());

        // Start capturing the console output
        testing::internal::CaptureStdout();

        if constexpr (std::is_void_v<Ret>) {
            std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
        } else {
            funcOutput = std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
        }

        // Stop capturing the console output
        std::cin.rdbuf(cinBuffer);
        std::string consoleOutput = testing::internal::GetCapturedStdout();

        // Return the function and console outputs
        if constexpr (std::is_void_v<Ret>) {
            return std::make_tuple(nullptr, consoleOutput);
        }
        return std::make_tuple(funcOutput, consoleOutput);
    }

private:
    static std::string printAnswersArray(const std::vector<std::string>& validAnswers);
    static std::string toLower(const std::string& str);
    static std::string trim(const std::string& str);
    static std::string formailzeAnswer(const std::string& answer, const bool& caseSensitive);
};

#endif // UTILS_H
