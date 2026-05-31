#include "CoreManager.hpp"

CoreManager::CoreManager() : _entityManger(), _componentManager(), _systemManager()
{

}

CoreManager::~CoreManager()
{

}

template <typename T>
void CoreManager::registerComponent()
{
    _componentManager.registerComponent<T>();
}

template <typename T>
void CoreManager::registerSystem()
{
    _systemManager.registerSystem<T>();
}

template <typename T>
void CoreManager::entityAddComponent(Entity entity, T component)
{
    _componentManager.addComponent(entity, component)
}