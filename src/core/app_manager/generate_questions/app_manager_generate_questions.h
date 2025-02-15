#ifndef APP_MANAGER_GENERATE_QUESTIONS_H
#define APP_MANAGER_GENERATE_QUESTIONS_H

#include <interfaces/app_manager.interface.h>

class AppManagerGenerateQuestions : public IAppManager {
public:
    ~AppManagerGenerateQuestions() override = default;
    int run() override;
};

#endif // APP_MANAGER_GENERATE_QUESTIONS_H
