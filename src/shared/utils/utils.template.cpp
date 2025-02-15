#include <gtest/gtest.h>

static std::string restoreInputAndCaptureOutput(std::streambuf* cinBuffer) {
    std::cin.rdbuf(cinBuffer);
    return testing::internal::GetCapturedStdout();
}

// Static function verion
template <typename F, typename... Args>
static auto invokeAndCaptureOutput(F&& func, std::string input, Args&&... args) {
    // Detect the return type of the function
    using Ret = std::invoke_result_t<F, Args...>;

    // Simulate the user input
    std::istringstream inputBuffer(input);
    std::streambuf* cinBuffer = std::cin.rdbuf(inputBuffer.rdbuf());

    // Start capturing the console output
    testing::internal::CaptureStdout();

    // Return the function and console outputs
    if constexpr (std::is_void_v<Ret>) {
        std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
        return std::make_tuple(nullptr, restoreInputAndCaptureOutput(cinBuffer));
    } else {
        Ret funcOutput = std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
        return std::make_tuple(funcOutput, restoreInputAndCaptureOutput(cinBuffer));
    }
}

// Member function version
template <typename Obj, typename Ret, typename... Args>
static auto invokeAndCaptureOutput(Ret (Obj::*memFunc)(Args...), std::string input, Obj* obj, Args... args) {
    // Simulate the user input
    std::istringstream inputBuffer(input);
    std::streambuf* cinBuffer = std::cin.rdbuf(inputBuffer.rdbuf());

    // Start capturing the console output
    testing::internal::CaptureStdout();

    // Return the function and console outputs
    if constexpr (std::is_void_v<Ret>) {
        (obj->*memFunc)(args...);
        return std::make_tuple(nullptr, restoreInputAndCaptureOutput(cinBuffer));
    } else {
        Ret funcOutput = (obj->*memFunc)(args...);
        return std::make_tuple(funcOutput, restoreInputAndCaptureOutput(cinBuffer));
    }
}
