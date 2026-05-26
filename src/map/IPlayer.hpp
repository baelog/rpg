#ifndef IPLAYER
#define IPLAYER

#include <SFML/Graphics/RenderWindow.hpp>

class IPlayer {        
    public:
        
        // void *on_colide;
        // void (*move)(struct my_s*);
        #ifndef SERVER
        virtual void print(sf::RenderWindow *window) = 0;
        #endif
};

#endif