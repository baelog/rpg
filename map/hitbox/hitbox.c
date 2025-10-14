#include <fcntl.h>
#include <sys/stat.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hitbox.h"

// #include <SFML/Graphics.h>
// #include <SFML/Graphics/ConvexShape.h>
// #include <SFML/Graphics/Color.h>

// sfConvexShape* createTriangle(sfConvexShape* triangle, struct triangle t, int n) {

//     // int c = 255 / ((n / 10) + 1);
//     sfColor a = {255, 255, 0, 100};

//     // printf("%d, %d\n", t.a.x, t.a.y);
//     // printf("%d, %d\n", t.b.x, t.b.y);
//     // printf("%d, %d\n", t.a.x, t.a.y);

//     sfConvexShape_setPoint(triangle, 0, (sfVector2f){(int)t.a.x, (int)t.a.y});
//     sfConvexShape_setPoint(triangle, 1, (sfVector2f){(int)t.b.x, (int)t.b.y});
//     sfConvexShape_setPoint(triangle, 2, (sfVector2f){(int)t.c.x, (int)t.c.y});

//     sfConvexShape_setFillColor(triangle, a);

//     /** Broke the shape for no reason */
//     // sfConvexShape_setOutlineThickness(triangle, 2.f);
//     // sfConvexShape_setOutlineColor(triangle, a);

//     return triangle;
// }

int maxXY(struct fileContent *info)
{
    int max = 0;
    for (int i = 0; i < info->size; i++) {
        if (max < info->t[i].a.x)
            max = max < info->t[i].a.x;
        if (max < info->t[i].a.y)
            max = max < info->t[i].a.y;
        if (max < info->t[i].b.x)
            max = max < info->t[i].b.x;
        if (max < info->t[i].b.y)
            max = max < info->t[i].b.y;
        if (max < info->t[i].c.x)
            max = max < info->t[i].c.x;
        if (max < info->t[i].c.y)
            max = max < info->t[i].c.y;
    }
    return max;
}

struct hitboxInfo *getHitbox(char *hitboxFile)
{
    int fd = open(hitboxFile, O_RDONLY);
    if (fd < 0) {
        perror("error while opening file");
        return NULL;
    }

    struct stat st;
    if (0 > stat(hitboxFile, &st)) {
        perror("error while stat");
        return NULL;
    }
    
    char *buff = malloc(sizeof(char) * st.st_size);
    if (!buff) {
        perror("error wile allocting buffer");
        return NULL;
    }

    if (0 > read(fd, buff, st.st_size)) {
        perror("error while reading");
        return NULL;
    }

    struct hitboxInfo *hitbox = malloc(sizeof(struct hitboxInfo));

    if (!hitbox) {
        free(buff);
        buff = NULL;
        return NULL;
    }
    
    hitbox->triangleArray = buff;
    hitbox->radius = maxXY((struct fileContent*)buff);
    
    return (hitbox);
}
