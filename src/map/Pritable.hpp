#ifndef PRITABLE_H
#define PRITABLE_H

#include <SFML/Graphics/RenderWindow.hpp>

class IPrintable {

    virtual void print(sf::RenderWindow*);
};

#endif