#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include <interfaces/app_manager.interface.h>

class AppManager : public IAppManager {
public:
    ~AppManager() override = default;
    int run() override;
};

#endif // APP_MANAGER_H
