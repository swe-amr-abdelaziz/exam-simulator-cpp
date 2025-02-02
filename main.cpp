#include "application_manager.h"

int main(int argc, char* argv[]) {
    try {
        ::testing::InitGoogleTest(&argc, argv);
        RunMode runMode = Utils::getAppRunMode(argc, argv);
        std::unique_ptr<ApplicationManager> appManager = std::make_unique<ApplicationManager>(runMode);
        return appManager->run();
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    }
}
