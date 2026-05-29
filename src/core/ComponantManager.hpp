#ifndef COMPONANT_MANAGER_HPP
#define COMPONANT_MANAGER_HPP

#include "ComponantAtribution.hpp"

class ComponantManager {
public:
    ComponantManager();
    ~ComponantManager();
    template <typename T>
    void registerComponant<T>();
    template <typename T>
    ComponantValue getcomponantValue(T componant);
    
    template <typename T>
    T& getData(Entity entity);
    

private:
    std::unordered_map<const char *, ComponantValue> _componantTypes
    std::unordered_map<const char *, ComponantAtribution<T>> _componantTypes;

};

#endif