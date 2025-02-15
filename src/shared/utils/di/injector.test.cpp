#include <gtest/gtest.h>

#include <constants/enums.h>
#include <constants/messages.h>
#include <utils/di/injector.h>

TEST(InjectorTest, should_return_normal_app_manager) {
    const Injector& injector = getInjector(Enums::RunMode::NORMAL);
    std::shared_ptr<IAppManager> appManager = injector.create<std::shared_ptr<IAppManager>>();

    ASSERT_NE(appManager, nullptr);

    AppManager* normalPtr = dynamic_cast<AppManager*>(appManager.get());
    EXPECT_NE(normalPtr, nullptr);
}

TEST(InjectorTest, should_return_test_app_manager) {
    const Injector& injector = getInjector(Enums::RunMode::TEST);
    std::shared_ptr<IAppManager> appManager = injector.create<std::shared_ptr<IAppManager>>();

    ASSERT_NE(appManager, nullptr);

    AppManagerTest* testPtr = dynamic_cast<AppManagerTest*>(appManager.get());
    EXPECT_NE(testPtr, nullptr);
}

TEST(InjectorTest, should_return_generate_questions_app_manager) {
    const Injector& injector = getInjector(Enums::RunMode::GENERATE_QUESTIONS);
    std::shared_ptr<IAppManager> appManager = injector.create<std::shared_ptr<IAppManager>>();

    ASSERT_NE(appManager, nullptr);

    AppManagerGenerateQuestions* genPtr = dynamic_cast<AppManagerGenerateQuestions*>(appManager.get());
    EXPECT_NE(genPtr, nullptr);
}

TEST(ApplicationManagerTest, should_throw_exception_when_passing_invalid_run_mode) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
    auto invalidRunMode = static_cast<Enums::RunMode>(-1);
#pragma GCC diagnostic pop

    EXPECT_THROW(
        {
            try {
                const Injector& injector = getInjector(invalidRunMode);
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_RUN_MODE, ex.what());
                throw;
            }
        },
        std::exception);
}
