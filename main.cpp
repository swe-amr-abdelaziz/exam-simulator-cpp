#include <constants/enums.h>
#include <interfaces/app_manager.interface.h>
#include <utils/di/injector.h>
#include <utils/utils.h>

int main(int argc, char* argv[]) {
    try {
        ::testing::InitGoogleTest(&argc, argv);
        RunMode runMode = Utils::getAppRunMode(argc, argv);
        const auto& injector = getInjector(runMode);
        auto appManager = injector.create<std::shared_ptr<IAppManager>>();
        return appManager->run();
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    }
}
