#ifndef IOBJECT
#define IOBJECT

#include <SFML/Graphics/RenderWindow.hpp>

class IObject {
    virtual void print(sf::RenderWindow*) = 0;
};

#endif