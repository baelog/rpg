#include "component.h"

struct Component *createComponent(struct Component *list, int type, void *data) {
    struct Component *new = malloc(sizeof(struct Component));

    if (!new)
        return (list);

    new->next = list;
    new->type = type;
    new->data = data;

    return new;
}