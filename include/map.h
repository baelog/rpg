
#ifndef MAP_H_
#define MAP_H_

#include <SFML/System/Vector2.h>
#include <SFML/System/Clock.h>
#include <SFML/Graphics/Types.h>

#define MAX_PLAYER 10

typedef struct grid_s grid_t;

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
    void (*print)(struct player_s*, sfRenderWindow*);
#endif
    sfClock *clock;
    void *on_colide;
    void (*move)(struct player_s*);
    void *on_destroy;
    int id;
    int state;
}player_t;

typedef struct world_s {
    player_t *player[MAX_PLAYER];
    tiles_t ***map;
    int player_count;
}world_t;

tiles_t *create_ground(sfVector2f);
tiles_t *create_wall(sfVector2f);

player_t *create_other_player(sfVector2f pos, int id);
player_t *create_me(sfVector2f pos, int id);

tiles_t ***create_scene_object(grid_t*);
char **handle_file(char*);

#endif /* !MAP_H_ */

