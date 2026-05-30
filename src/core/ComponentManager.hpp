#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include "ComponentAtribution.hpp"
#include <memory>

class ComponentManager {
public:
    ComponentManager();
    ~ComponentManager();

    template <typename T>
    void registerComponent();
    
    template <typename T>
    ComponentValue getcomponentValue(T component);
    
    template <typename T>
    T& getData(Entity entity);
    
    template <typename T>
    void addComponent(Entity entity, T component);

    template <typename T>
    void removeComponent(Entity entity);

    template <typename T>
    void destroyEntity(Entity entity);
;

private:
    std::unordered_map<const char *, ComponentValue> _componentValues;
    std::unordered_map<const char *, std::shared_ptr<IComponentAtribition>> _componentArray;
    uint32_t _componentRegister;
    template <typename T>
    std::shared_ptr<ComponentAtribution<T>> getComponentList();
    
};

#endif