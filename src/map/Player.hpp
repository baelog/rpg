#ifndef PLAYER
#define PLAYER

#include <SFML/System/Vector2.hpp>
// #include <SFML/Graphics/Types.hpp>
// #include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player {
    private:

        // sf::Image *image;
    #ifndef SERVER
        static sf::Texture *_texture;
        static sf::Sprite *_sprite;
    #endif
        sf::Clock _clock;
        int _id;
        int _state;
        sf::Vector2f _position;
        
        public:
        
        // void *on_colide;
        // void *on_destroy;
        Player(sf::Vector2f &position, int &id);
        ~Player();
        void (*move)(struct my_s*);
        #ifndef SERVER
        void print(sf::RenderWindow *);
        #endif
};

#endif