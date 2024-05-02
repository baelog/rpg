#include "wall.h"
#include <stdlib.h>

static void on_colide(void)
{

}

static void print(struct wall_s *self, sfRenderWindow *window)
{
    sfSprite_setPosition(self->spirte, self->position);
    sfRenderWindow_drawSprite(window, self->spirte, NULL);
}

static void on_destroy(void)
{

}

tiles_t *create_wall(sfVector2f pos)
{
    struct wall_s *wall = malloc(sizeof(struct wall_s));
    static sfSprite *sprite = NULL;
    static sfTexture* texture = NULL;
    
    if (!texture) {
        sfImage *image = sfImage_create(50, 50);
        for (unsigned int x = 0; x < 50; x++) {
            for (unsigned int y = 0; y < 50; y++)
                sfImage_setPixel(image, x, y, sfRed);
    }
    texture = sfTexture_create(50, 50);
    sfTexture_updateFromImage(texture, image, 0, 0);

    }
    if (!sprite) {
        sprite = sfSprite_create();
        
        sfSprite_setTexture(sprite, texture, sfFalse);
    }
    wall->position = pos;
    wall->on_colide = &on_colide;
    wall->print = &print;
    wall->on_destroy = &on_destroy;
    wall->spirte = sprite;

    return (tiles_t*)wall;
}


