#include "SystemManager.hpp"

SystemManager::SystemManager() : _systemTypes{}, _systemSignatures{}
{

}

SystemManager::~SystemManager()
{

}

template <typename T>
void SystemManager::registerSystem()
{
    const char *index = typeid(T).name();
    
    _systemTypes[index] = std::make_shared<T>();
}
template <typename T>
void SystemManager::setsignature(Signature signature)
{
    const char *index = typeid(T).name();
    
    _systemSignatures[index] = signature;
}

template <typename T>
Signature SystemManager::getsignature()
{
    const char *index = typeid(T).name();
    
    return _systemSignatures[index];
}

void SystemManager::destroyEntiy(Entity entity)
{
    for (auto system : _systemTypes) {
        system.second->entities.erase(entity);
    }
}