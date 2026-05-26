
#ifndef WALL_H_
#define WALL_H_

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "IObject.hpp"


//TODO it will become a colider object
struct Wall : public IObject {
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
        Wall(sf::Vector2f &position);
        ~Wall();
        // void (*move)(struct my_s*);
        #ifndef SERVER
        void print(sf::RenderWindow *window);
        #endif
};

#endif /* !WALL_H_ */