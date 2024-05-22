
#ifndef PLAYER_MAP_H_
#define PLAYER_MAP_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Sprite.h>

struct my_s {
    sfVector2f position;
#ifndef SERVER
    sfSprite *spirte;
    void (*print)(struct my_s*, sfRenderWindow*);
#endif
    void *on_colide;
    void *on_destroy;
    int id;
};

#endif /* !PLAYER_H_ */
