#include <gtest/gtest.h>

#include <application_manager/application_manager.h>
#include <constants/enums.h>
#include <constants/messages.h>

TEST(ApplicationManagerTest, given_invalid_run_mode_when_run_then_throw) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
    auto invalidRunMode = static_cast<Enums::RunMode>(-1);
#pragma GCC diagnostic pop

    EXPECT_THROW(
        {
            try {
                std::unique_ptr<ApplicationManager> appManager =
                    std::make_unique<ApplicationManager>(invalidRunMode);
                appManager->run();
            } catch (const std::exception& ex) {
                EXPECT_EQ(Messages::INVALID_RUN_MODE, ex.what());
                throw;
            }
        },
        std::exception);
}
