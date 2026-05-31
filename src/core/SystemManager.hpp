#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "types.hpp"
#include "system.hpp"

#include <memory>

class SystemManager {
public :
    SystemManager();
    ~SystemManager();
    template <typename T>
    void registerSystem();
    template <typename T>
    void setsignature(Signature);
    template <typename T>
    Signature getsignature();
    void destroyEntiy(Entity entity);

private:
    std::unordered_map<const char *, std::shared_ptr<System>> _systemTypes;
    std::unordered_map<const char *, Signature> _systemSignatures;

};

#endif