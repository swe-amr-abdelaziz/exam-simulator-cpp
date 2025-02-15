#ifndef IAPP_MANAGER_H
#define IAPP_MANAGER_H

class IAppManager {
public:
    virtual ~IAppManager() = default;
    virtual int run() = 0;
};

#endif // IAPP_MANAGER_H
