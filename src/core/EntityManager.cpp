#include "EntityManager.hpp"

EntityManger::EntityManger() : _entityComponant{}, _availableEntityCount(MAX_ENTITIES)
{
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        _availableEntity[entity] = entity;
    }
}

EntityManger::~EntityManger() {
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        _entityComponant[entity].clear();
    }
}

Entity EntityManger::createEntity()
{
    Entity id = _availableEntity[_availableEntityCount - 1];
    _availableEntity[_availableEntityCount - 1] = 0;
    _availableEntityCount--;

    return id;
}


void EntityManger::destroyEntity(Entity entity)
{
    _availableEntity[_availableEntityCount] = entity;
    _availableEntityCount++;

    _entityComponant[entity].clear();
}

void EntityManger::setSignature(ComponentSignature signature, Entity entity)
{
    _entityComponant[entity][signature] = true;
}

Signature EntityManger::getSignature(Entity entity)
{
    return _entityComponant[entity];
}

