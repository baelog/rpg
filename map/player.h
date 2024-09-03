
#ifndef PLAYER_MAP_H_
#define PLAYER_MAP_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Clock.h>

struct my_s {
    sfVector2f position;
#ifndef SERVER
    sfSprite *spirte;
    void (*print)(struct my_s*, sfRenderWindow*);
#endif
    sfClock *clock;
    void *on_colide;
    void (*move)(struct my_s*);
    void *on_destroy;
    int id;
    int state;
};

#endif /* !PLAYER_H_ */
