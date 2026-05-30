#include "ComponentAtribution.hpp"

IComponentAtribition::~IComponentAtribition()
{

}

template<typename T>
ComponentAtribution<T>::ComponentAtribution() : _componentData{}, _entitycomponentIndex{}, _size(0)
{

}



template<typename T>
ComponentAtribution<T>::~ComponentAtribution()
{
    _componentData.fill({});
    _entitycomponentIndex.clear()
    _size = 0;
}

template<typename T>
void ComponentAtribution<T>::setEntityComponent(Entity entity, T component)
{
    if (_entitycomponentIndex.find(entity) == _entitycomponentIndex.end())
        return;
    _entitycomponentIndex[entity] = _size;
    _componentData[_size] = component;
    _size++;
}

template<typename T>
void ComponentAtribution<T>::destroyEntityComponent(Entity entity)
{
    if (_entitycomponentIndex.find(entity) == _entitycomponentIndex.end())
        return;
    _size--;
    uint32_t position = _entitycomponentIndex[entity];
    _componentData[position] = _componentData[size];
    _entitycomponentIndex.erase(_size);
}

template <typename T>
T &ComponentAtribution<T>::getData(Entity entity) const
{
    uint32_t position = _entitycomponentIndex[entity];

    return _componentData[size];
}