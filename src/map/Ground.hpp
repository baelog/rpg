
#ifndef GROUND_H_
#define GROUND_H_

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "IObject.hpp"



struct Ground : public IObject {
    private:

        // sf::Image *image;
    #ifndef SERVER
        static sf::Texture *_texture;
        static sf::Sprite *_sprite;
    #endif
        int _type;
        sf::Vector2f _position;
        
    public:
        
        // void *on_colide;
        // void *on_destroy;
        Ground(sf::Vector2f &position);
        ~Ground();
        // void (*move)(struct my_s*);
        #ifndef SERVER
        void print(sf::RenderWindow *window);
        #endif
};

#endif