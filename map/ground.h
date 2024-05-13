

#ifndef GROUND_H_
#define GROUND_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>

typedef struct tiles_s tiles_t;


struct ground_s{
    sfVector2f position;
#ifndef SERVER
    sfSprite *spirte;
    void (*print)(void);
#endif
    void *on_colide;
    void *on_destroy;
    int (*get_type)(void);
    int spawn;
};

#endif /* !GROUND_H_ */
