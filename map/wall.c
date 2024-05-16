#include "wall.h"
#include <stdlib.h>
#include <stdio.h>
#ifndef SERVER
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Image.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Sprite.h>
#endif

static void on_colide(void)
{

}

static void print(struct wall_s *self, sfRenderWindow *window)
{
    #ifndef SERVER
    sfSprite_setPosition(self->spirte, self->position);
    sfRenderWindow_drawSprite(window, self->spirte, NULL);
    #endif
}

static void on_destroy(void)
{

}

static int get_type(void)
{
    return 1;
}


tiles_t *create_wall(sfVector2f pos)
{
    struct wall_s *wall = malloc(sizeof(struct wall_s));
    #ifndef SERVER
    static sfSprite *sprite = NULL;
    static sfTexture* texture = NULL;
    
    if (!texture) {
        sfImage *image = sfImage_create(50, 50);
        // if (!image) {
        //     write(1, "error can't create image\n", strlen("error can't create image\n"));
        //     // exit(0);
        // }
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
    wall->spirte = sprite;
    wall->print = &print;
    #endif
    wall->position = pos;
    wall->on_colide = &on_colide;
    wall->on_destroy = &on_destroy;
    wall->get_type = &get_type;
    wall->spawn = 0;

    return (tiles_t*)wall;
}


