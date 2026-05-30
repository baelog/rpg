#ifndef COMPONENT_ATRIBUTION_HPP
#define COMPONENT_ATRIBUTION_HPP

#include "types.hpp"


class IComponentAtribition {
    virtual ~IComponentAtribition();
    virtual void destroyEntityComponent(Entity entity) = 0;
    
};

template <typename T>
class ComponentAtribution : IComponentAtribition {
public:
    ComponentAtribution();
    ~ComponentAtribution();

    void setEntityComponent(Entity entity, T component);
    void destroyEntityComponent(Entity entity) override;
    T &getData(Entity entity) const;

    
private:
    std::array<T, MAX_ENTITIES> _componentData;
    std::unordered_map<Entity, uint32_t> _entitycomponentIndex;
    uint32_t _size;

};

#endif