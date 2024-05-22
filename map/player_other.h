
#ifndef PLAYER_OTHER_H_
#define PLAYER_OTHER_H_


#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>

#define MAX_PLAYER 10

struct other_s {
    sfVector2f position;
#ifndef SERVER
    sfSprite *spirte;
    void (*print)(struct other_s*, sfRenderWindow*);
#endif
    void *on_colide;
    void *on_destroy;
    int id;
};

#endif /* !PLAYER_OTHER_H_ */
