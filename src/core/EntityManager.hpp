#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "types.hpp"

#include <unordered_map>
#include <array>
#include <queue>

class EntityManger {
public:
    EntityManger();
    // ~EntityManger();
    Entity createEntity();
    void destroyEntity(Entity);
    void setSignature(ComponentSignature Signature, Entity entity);
    Signature EntityManger::getSignature(Entity entity);



private:
    std::array<Signature, MAX_ENTITIES> _entityComponant;
    Entity _availableEntity[MAX_ENTITIES];
    uint32_t _availableEntityCount;
};

#endif