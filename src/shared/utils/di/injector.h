#ifndef INJECTOR_H
#define INJECTOR_H

#include <boost/di.hpp>

#include <app_manager/generate_questions/app_manager_generate_questions.h>
#include <app_manager/normal/app_manager.h>
#include <app_manager/test/app_manager_test.h>
#include <constants/enums.h>
#include <constants/messages.h>
#include <interfaces/app_manager.interface.h>

namespace di = boost::di;

using Injector = boost::di::injector<std::shared_ptr<IAppManager>>;

inline const Injector& getInjector(Enums::RunMode runMode = Enums::RunMode::NORMAL) {
    static const Injector normalInjector =
        di::make_injector(di::bind<IAppManager>().to<AppManager>().in(di::singleton));
    static const Injector testInjector =
        di::make_injector(di::bind<IAppManager>().to<AppManagerTest>().in(di::singleton));
    static const Injector generateQuestionsInjector =
        di::make_injector(di::bind<IAppManager>().to<AppManagerGenerateQuestions>().in(di::singleton));

    switch (runMode) {
        case Enums::RunMode::NORMAL:
            return normalInjector;
        case Enums::RunMode::TEST:
            return testInjector;
        case Enums::RunMode::GENERATE_QUESTIONS:
            return generateQuestionsInjector;
        default:
            throw std::runtime_error(Messages::INVALID_RUN_MODE);
    }
}

#endif // INJECTOR_H
