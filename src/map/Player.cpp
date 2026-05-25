#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

sf::Texture *Player::_texture = NULL;
sf::Sprite *Player::_sprite = NULL;

Player::Player(sf::Vector2f &position, int &id) : _position(position), _id(id), _state(0), _clock()
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

Player::~Player()
{
    delete _sprite;
    delete _texture;
}