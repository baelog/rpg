#include "ground.h"
#include <stdlib.h>
#ifndef SERVER
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Image.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Sprite.h>
#endif



static void on_colide(void)
{

}

static void print(struct ground_s *self, sfRenderWindow *window)
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
    return 2;
}


tiles_t *create_ground(sfVector2f pos)
{
    struct ground_s *ground = malloc(sizeof(struct ground_s));
    #ifndef SERVER
    static sfSprite *sprite = NULL;
    static sfTexture* texture = NULL;
    
    if (!texture) {
        sfImage *image = sfImage_create(50, 50);
        for (unsigned int x = 0; x < 50; x++) {
            for (unsigned int y = 0; y < 50; y++)
                sfImage_setPixel(image, x, y, sfGreen);
    }
        texture = sfTexture_create(50, 50);
        sfTexture_updateFromImage(texture, image, 0, 0);

    }
    if (!sprite) {
        sprite = sfSprite_create();
        
        sfSprite_setTexture(sprite, texture, sfFalse);
    }
    ground->spirte = sprite;
    ground->print = &print;
    #endif
    ground->position = pos;
    ground->on_colide = &on_colide;
    ground->on_destroy = &on_destroy;
    ground->get_type = &get_type;
    ground->spawn = 0;

    return (tiles_t*)ground;
}


