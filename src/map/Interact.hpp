
#ifndef INTERACT_H_
#define INTERACT_H_

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "IObject.hpp"


//TODO it will become a colider object
struct Interact : public IObject {
    private:

        // sf::Image *image;
    #ifndef SERVER
        static sf::Texture *_texture;
        static sf::Sprite *_sprite;
    #endif
        // int _spwan;
        sf::Vector2f _position;
        int _type;
        
    public:
        
        // void *on_colide;
        // void *on_destroy;
        Interact(sf::Vector2f &position);
        ~Interact();
        // void (*move)(struct my_s*);
        #ifndef SERVER
        void print(sf::RenderWindow *window);
        #endif
};

#endif 