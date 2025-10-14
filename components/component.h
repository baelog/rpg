
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "../network/protocol/types.h"

enum StatusEffect {
    POISON,
    REGENERATION,
    STUN,
    ROOT,
    BUMP
};

struct IStatus {
    enum StatusEffect effect;
    int duration;
};

struct IComponent {
    void (*action)(void* client, player_t *player, struct IStatus *status);
};

enum ComponentType {
    HIYBOX
};

struct Component {
    int type;
    void *data;
    struct Component *next;
};

#endif /* !COMPONENT_H_ */
