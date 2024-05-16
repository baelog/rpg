

#ifndef WALL_H_
#define WALL_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Sprite.h>

typedef struct tiles_s tiles_t;


struct wall_s{
    sfVector2f position;
#ifndef SERVER
    sfSprite *spirte;
    void (*print)(struct wall_s*, sfRenderWindow*);
#endif
    void *on_colide;
    void *on_destroy;
    int (*get_type)(void);
    int spawn;
};

#endif /* !WALL_H_ */
