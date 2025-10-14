#ifndef MAP_SPRITE
#define MAP_SPRITE

#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>

int createSprite(char *spriteFile, sfTexture **texture, sfSprite **sprite, sfIntRect rect);

#endif
