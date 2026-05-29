#ifndef COMPONANT_ATRIBUTION_HPP
#define COMPONANT_ATRIBUTION_HPP

#include "types.hpp"


class IComponantAtribition {
    virtual ~IComponantAtribition();
    virtual void destroyEntityComponant(Entity entity) = 0;
    
};

template <typename T>
class ComponantAtribution : IComponantAtribition {
public:
    ComponantAtribution();
    ~ComponantAtribution();

    void setEntityComponant(Entity entity, T componant);
    void destroyEntityComponant(Entity entity) override;
    T &getData(Entity entity) const;

    
private:
    std::array<T, MAX_ENTITIES> _componantData;
    std::unordered_map<Entity, uint32_t> _entitycomponantIndex;
    uint32_t _size;

};

#endif