#ifndef CORE_MANAGER_HPP
#define CORE_MANAGER_HPP

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"


class CoreManager {
public:
    CoreManager();
    ~CoreManager();

    template <typename T>
    void registerComponent();

    template <typename T>
    void registerSystem();

    template <typename T>
    void entityAddComponent(Entity entity, T component);

    template <typename T>
    void getsignature();

    template <typename T>
    void setsignature();

    template <typename T>
    void destroyEntity();

    template <typename T>
    void destroyEntity();
    
private:
    EntityManger _entityManger;
    ComponentManager _componentManager;
    SystemManager _systemManager;
};
#endif