#include "ComponantAtribution.hpp"

IComponantAtribition::~IComponantAtribition()
{

}

template<typename T>
ComponantAtribution<T>::ComponantAtribution() : _componantData{}, _entitycomponantIndex{}, _size(0)
{

}



template<typename T>
ComponantAtribution<T>::~ComponantAtribution()
{
    _componantData.fill({});
    _entitycomponantIndex.clear()
    _size = 0;
}

template<typename T>
void ComponantAtribution<T>::setEntityComponant(Entity entity, T componant)
{
    if (_entitycomponantIndex.find(entity) == _entitycomponantIndex.end())
        return;
    _entitycomponantIndex[entity] = _size;
    _componantData[_size] = componant;
    _size++;
}

template<typename T>
void ComponantAtribution<T>::destroyEntityComponant(Entity entity)
{
    if (_entitycomponantIndex.find(entity) == _entitycomponantIndex.end())
        return;
    _size--;
    uint32_t position = _entitycomponantIndex[entity];
    _componantData[position] = _componantData[size];
    _entitycomponantIndex.erase(_size);
}

template <typename T>
T &ComponantAtribution<T>::getData(Entity entity) const
{
    uint32_t position = _entitycomponantIndex[entity];

    return _componantData[size];
}