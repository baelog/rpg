
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "../network/protocol/types.h"

enum Status_effect {
    POISON,
    REGENERATION,
    STUN,
    ROOT,
    BUMP
};

struct IStatus {
    Status_effect effect;
    int duration;
};

struct IComponent {
    void (*action)(void* client, player_t *player, IStatus status);

};

#endif /* !COMPONENT_H_ */
