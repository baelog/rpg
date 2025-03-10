#ifndef COMBAT_H_
#define COMBAT_H_

#define ISO_HEIGHT 20
#define ISO_WIDTH 20
#define ISO_X 16
#define ISO_Y 16

#define PI 3.1415

#define MAX_Y 1000
#define MAX_X 1500

#define SQUARE_OFFSET 20

#define HEXAGONE_TRIANGLE 6
#define TRIANGLE_VERTICE 3

#define ROTATION_ANGLE PI/4

#define ABS(v) (v > 0 ? v : v * -1)

#define HEXAGONE_EDGE_LEN 50
#define HEXAGONE_BASE_ANGLE PI/2
#define TRIANGLE_OUTLINE_THICKNESS 0
#define TRANGLE_ANGLE PI/3
#define TRIANGLE_HEIGHT (HEXAGONE_EDGE_LEN * sin(TRANGLE_ANGLE))

#include <SFML/Graphics/ConvexShape.h>
#include <SFML/System/Vector2.h>
#include <SFML/System/Vector3.h>

typedef struct Triangle_s {
    sfConvexShape *shape;
    sfVector3f vertice[TRIANGLE_VERTICE];
}Triangle_t;

typedef struct Hexagone_s {
    Triangle_t triangle[HEXAGONE_TRIANGLE];
    sfVector3f vertice;
    sfColor color;
}Hexagone_t;

typedef struct Square {
    int position[3];
    int segment[4][2];
    void(*rotate)(void);
} Square;

#endif /* !COMBAT_H_ */
