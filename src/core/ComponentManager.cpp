#include "ComponentManager.hpp"

ComponentManager::ComponentManager() : _componentValues{}, _componentArray{}, _componentRegister(0)
{
    
}

ComponentManager::~ComponentManager()
{
    
}

template <typename T>
void ComponentManager::registerComponent()
{
    const char *index = typeid(T).name();

    _componentValues[index] = _componentRegister;
    _componentRegister[index] = std::make_shared<ComponentAtribution<T>>();
    _componentRegister++;

}


template <typename T>
ComponentValue ComponentManager::getcomponentValue(T component)
{
    return _componentArray[typeid(T).name()];
}

template <typename T>
T& ComponentManager::getData(Entity entity)
{
    std::shared_ptr<ComponentAtribution<T>> componentList = getComponentList<T>();

    return (componentList->getData(entity));
}

template <typename T>
void ComponentManager::addComponent(Entity entity, T component)
{
    std::shared_ptr<ComponentAtribution<T>> componentList = getComponentList<T>();

    componentList->setEntityComponent(entity, component);
}

template <typename T>
void ComponentManager::removeComponent(Entity entity)
{
    std::shared_ptr<ComponentAtribution<T>> componentList = getComponentList<T>();

    componentList->destroyEntityComponent(entity);
}

template <typename T>
void ComponentManager::destroyEntity(Entity entity)
{
    for (const auto component : _componentArray) {
        auto cpmnnt = component.second;
        cpmnnt->destroyEntityComponent(entity);
    }
}

template <typename T>
std::shared_ptr<ComponentAtribution<T>> ComponentManager::getComponentList()
{
    const char *index = typeid(T).name();

    return (std::shared_ptr<ComponentAtribution<T>>(_componentRegister[index]));
}
