#ifndef APP_MANAGER_TEST_H
#define APP_MANAGER_TEST_H

#include <interfaces/app_manager.interface.h>

class AppManagerTest : public IAppManager {
public:
    ~AppManagerTest() override = default;
    int run() override;
};

#endif // APP_MANAGER_TEST_H
