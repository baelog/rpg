
#ifndef MAP_H_
#define MAP_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>

#define MAX_PLAYER 10

enum tiles {
    PLAYER,
    WALL,
    GROUND,
};

typedef struct tiles_s{
    sfVector2f position;
#ifndef SERVER
    sfSprite *spirte;
    void (*print)(struct tiles_s*, sfRenderWindow*);
#endif
    void *on_colide;
    void *on_destroy;
    int (*get_type)(void);
    int spawn;
}tiles_t;

typedef struct player_s {
    sfVector2f position;
#ifndef SERVER
    sfSprite *spirte;
    void (*print)(struct tiles_s*, sfRenderWindow*);
#endif
    void *on_colide;
    void *on_destroy;
    int id;
}player_t;

typedef struct world_s {
    player_t player[MAX_PLAYER];
    tiles_t ***map;
    int player_count;
}world_t;

tiles_t *create_ground(sfVector2f);
tiles_t *create_wall(sfVector2f);

tiles_t ***create_scene_object(grid_t);

#endif /* !MAP_H_ */

