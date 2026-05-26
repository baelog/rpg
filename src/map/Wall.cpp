#include "Wall.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

sf::Texture *Wall::_texture = NULL;
sf::Sprite *Wall::_sprite = NULL;

Wall::Wall(sf::Vector2f &position) : _position(position)
{
    #ifndef SERVER
    
    if (!_texture) {
        sf::Image image = sf::Image({50, 50}, sf::Color::Blue);
        // for (unsigned int x = 0; x < 50; x++) {
        //     for (unsigned int y = 0; y < 50; y++)
        //         sfImage_setPixel(image, x, y, sfBlue);
        // }
        _texture = new sf::Texture(image);
        // texture = sfTexture_create(50, 50);
        // sfTexture_updateFromImage(texture, image, 0, 0);

    }
    if (!_sprite) {
        //TODO change the rectangle rec for annimations
        _sprite = new sf::Sprite(*_texture);
        // sprite = sfSprite_create(); 
        // sfSprite_setTexture(sprite, texture, sfFalse);
    }
    // player->spirte = sprite;
    // player->print = &print;
    #endif
    // player->clock = sfClock_create();
    // player->state = 0;
    // player->position = pos;
    // player->on_colide = &on_colide;
    // player->move = &move;
    // player->on_destroy = &on_destroy;
    // player->get_type = &get_type;
    // player->id = id;
}

Wall::~Wall()
{
    delete _sprite;
    delete _texture;
}

void Wall::print(sf::RenderWindow *window)
{
    window->draw(*_sprite);
}
