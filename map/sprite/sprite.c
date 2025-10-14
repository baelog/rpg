#include "sprite.h"

int createSprite(char *spriteFile, sfTexture **texture, sfSprite **sprite, sfIntRect rect)
{
    if (!*texture) {
        *texture = sfTexture_createFromFile(spriteFile, &rect);
        if (!*texture)
            return -1;
    }
    if (!*sprite) {
        *sprite = sfSprite_create();
        if (!*sprite)
            return -2;
        sfSprite_setTexture(*sprite, *texture, sfFalse);
    }
    return 0;
}