#include "combat.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/RectangleShape.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <SFML/Graphics/View.h>

sfVector2f projectPoint(sfVector3f point) {
    double f = 0.7;
    return (sfVector2f){point.x, point.y * f};
    // return (sfVector2f){point.x, point.y};
}

sfVector3f rotateX(sfVector3f position, double distance, double angle) {
    double y = position.y * cos(angle) - position.z * sin(angle);
    double z = position.y * sin(angle) + position.z * cos(angle);
    position.y = y;
    position.z = z ;
    // printf("distance : %f\n", distance);
    return position;
}

float sign(sfVector2f p1, sfVector2f p2, sfVector2f p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int pointInTriangle(sfVector2f pt, sfVector3f v1, sfVector3f v2, sfVector3f v3)
{
    float d1, d2, d3;
    int has_neg, has_pos;

    d1 = sign(pt, (sfVector2f){v1.x, v1.y}, (sfVector2f){v2.x, v2.y});
    d2 = sign(pt, (sfVector2f){v2.x, v2.y}, (sfVector2f){v3.x, v3.y});
    d3 = sign(pt, (sfVector2f){v3.x, v3.y}, (sfVector2f){v1.x, v1.y});

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void trianglePrint(sfRenderWindow *window, Triangle_t *triangle, sfColor color)
{
    sfConvexShape_setFillColor(triangle->shape, color);
    sfRenderWindow_drawConvexShape(window, triangle->shape, NULL);
}

void triangleSetPosition(Triangle_t *triangle,sfVector3f position, int edge, double ang)
{
    double base = (ang) * (PI / 3.0) + HEXAGONE_BASE_ANGLE;

    double ang1 = base + (PI / 6);
    double ang2 = base - (PI / 6);

    triangle->vertice[0] = (sfVector3f){position.x, position.y, 1};
    // triangle->vertice[0] = (sfVector3f){position.x, position.y, position.z};
    triangle->vertice[1] = (sfVector3f){position.x + cos(ang1) * edge, position.y + sin(ang1) * (edge), 1};
    // triangle->vertice[1].z = triangle->vertice[1].y + triangle->vertice[1].x;
    triangle->vertice[2] = (sfVector3f){position.x + cos(ang2) * edge, position.y + sin(ang2) * (edge), 1};
    // triangle->vertice[2].z = triangle->vertice[2].y + triangle->vertice[2].x;
    triangle->vertice[0] = rotateX(triangle->vertice[0], ABS(position.y - triangle->vertice[0].y), ROTATION_ANGLE);
    triangle->vertice[1] = rotateX(triangle->vertice[1], ABS(position.y - triangle->vertice[1].y), ROTATION_ANGLE);
    triangle->vertice[2] = rotateX(triangle->vertice[2], ABS(position.y - triangle->vertice[2].y), ROTATION_ANGLE);
    // printf("pos z :%f %f, %f %f, %f %f,  %f %f\n",triangle->vertice[0].x, triangle->vertice[0].y, triangle->vertice[1].x, triangle->vertice[2].x, triangle->vertice[1].y, triangle->vertice[2].y, triangle->vertice[1].z, triangle->vertice[2].z);

    for (int i = 0; i < TRIANGLE_VERTICE; i++)
        // sfConvexShape_setPoint(triangle->shape, i, (sfVector2f){triangle->vertice[i].x  * 500 / (triangle->vertice[i].z), triangle->vertice[i].y * 500/ (triangle->vertice[i].z)});
        // sfConvexShape_setPoint(triangle->shape, i, (sfVector2f){triangle->vertice[i].x, triangle->vertice[i].y});
        sfConvexShape_setPoint(triangle->shape, i, projectPoint(triangle->vertice[i]));
}

void triangleCreate(Triangle_t *triangle)
{
    triangle->shape = sfConvexShape_create();
    sfConvexShape_setPointCount(triangle->shape, TRIANGLE_VERTICE);
    sfConvexShape_setOutlineThickness(triangle->shape, TRIANGLE_OUTLINE_THICKNESS);
    sfConvexShape_setOutlineColor(triangle->shape, sfBlack);
}

void hexagoneCreate(Hexagone_t *hexagone)
{
    for (int i = 0; i < HEXAGONE_TRIANGLE; i++)
        triangleCreate(&hexagone->triangle[i]);
}

void hexagoneSetPosition(Hexagone_t *hexagone, sfVector3f pos)
{
    for (int i = 0; i < HEXAGONE_TRIANGLE; i++)
        triangleSetPosition(&hexagone->triangle[i], pos, HEXAGONE_EDGE_LEN, i + PI/6);
}

void hexagoneDraw(sfRenderWindow *window, Hexagone_t *hexagone)
{
    for (int i = 0; i < HEXAGONE_TRIANGLE; i++)
        trianglePrint(window, &hexagone->triangle[i], hexagone->color);
}

void hexagoneSetColor(Hexagone_t *hexagone, sfColor color)
{
    memcpy(&hexagone->color, &color, sizeof(color));
}

int isPoint_insideHexagone(Hexagone_t *hexagone, sfVector2f point)
{
    for (int i = 0; i < HEXAGONE_TRIANGLE; i++) {
        if (pointInTriangle(point, hexagone->triangle[i].vertice[0], hexagone->triangle[i].vertice[1], hexagone->triangle[i].vertice[2]))
            return 1;
    }
    return 0;
}

// void createTriangle(Triangle_t *triangle, sfVector2f position, int edge, double ang)
// {
//     static sfConvexShape *shape[HEXAGONE_TRIANGLE] = { NULL };

//     static int ac_face = 0;

//     double base = (ang) * (PI / 3.0);

//     double ang1 = base + (PI / 6);
//     double ang2 = base - (PI / 6);

//     triangle->vertice[0] = (sfVector3f){position.x, position.y, 1};
//     triangle->vertice[1] = (sfVector3f){position.x + cos(ang1) * edge, position.y + sin(ang1) * (edge / 1.3), 1};
//     triangle->vertice[2] = (sfVector3f){position.x + cos(ang2) * edge, position.y + sin(ang2) * (edge / 1.3), 1};
//     // printf("%f %f\n%f %f\n%f %f\n\n",triangle->vertice[0].x,triangle->vertice[0].y,triangle->vertice[1].x, triangle->vertice[1].y, triangle->vertice[2].x,triangle->vertice[2].y );
//     if (!shape[ac_face]) {
//         shape[ac_face] = sfConvexShape_create();
//         sfConvexShape_setPointCount(shape[ac_face], TRIANGLE_VERTICE);
//         sfConvexShape_setOutlineThickness(shape[ac_face], 2);
//         sfConvexShape_setOutlineColor(shape[ac_face], sfBlack);
//     }
//     triangle->shape = shape[ac_face];
//     // write(1, "1\n", 2);
//     for (int i = 0; i < TRIANGLE_VERTICE; i++) {
//         sfConvexShape_setPoint(triangle->shape, i, (sfVector2f){triangle->vertice[i].x, triangle->vertice[i].y});
//     }
//     // sfConvexShape_setFillColor(triangle->shape, sfBlue);
//     return;
// }


int main(void)
{
    int rows = ISO_Y;
    int collumn = ISO_X;
    sfRenderWindow *window;
    sfVideoMode mode = {MAX_X, MAX_Y, 32};
    sfEvent event;
    sfView *view = sfView_create();
    // sfView_setViewport(view, (sfFloatRect){0, 0, MAX_X, MAX_Y});
    // sfView_setSize(view, (sfVector2f){MAX_X, MAX_Y});
    // sfView_setRotation(view, 45);
    window = sfRenderWindow_create(mode, "test", sfResize | sfClose, NULL);

    // sfRenderWindow* window;
    // sfUint32 windowPx[MAX_X * MAX_Y] = {0};
    sfColor c = {255, 0, 0, 255};
    
    // sfRectangleShape *rectangle = sfRectangleShape_create();
    // sfRectangleShape_setFillColor(rectangle, c);
    // sfRectangleShape_setOutlineColor(rectangle, c);
    // sfRectangleShape_setPosition(rectangle, (sfVector2f){0, 0});
    // sfRectangleShape_setSize(rectangle, (sfVector2f){SQUARE_OFFSET, SQUARE_OFFSET});
    sfRenderWindow_setFramerateLimit(window, 60);

    Hexagone_t hexagone = { 0 };
    // for (int i = 0; i < HEXAGONE_TRIANGLE; i++) {
    //     write(1, "t\n", 2);
    //     createTriangle(&hexagone.triangle[i], (sfVector2f){MAX_X / 2, MAX_Y / 2}, 100.,i);
    // }
    hexagoneCreate(&hexagone);
    
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        // for (int i = 0; i < rows; i++) {
        //     for (int j = 0; j < collumn; j++) {
        //         c.g = (i * (255 / rows));
        //         c.b = (j * (255 / rows));
        //         // sfRectangleShape_setFillColor(rectangle, c);
        //         int iso_x = ((i - j) * ISO_WIDTH / 2) + MAX_X / 2;
        //         int iso_y = ((i + j) * ISO_HEIGHT / 2);
        //         hexagoneSetColor(&hexagone, c);
        //         hexagoneSetPosition(&hexagone, (sfVector2f){iso_x, iso_y});
        //         hexagoneDraw(window, &hexagone);
        //         // printf("%d %d %d %d\n", iso_x, iso_y, i, j);
        //         // sfRectangleShape_setPosition(rectangle, (sfVector2f){iso_x, iso_y});
        //         // sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
        //     }
        // }
        sfVector2i cursorPosition = sfMouse_getPositionRenderWindow(window); 
        double offset = TRIANGLE_HEIGHT;
        // int isOffset = 0;

        // double isoXPrev = offset;
        // double isoYPrev = offset;
        // double isoZPrev = 0;
        // int isAbove = 0;
        for (int i = 0; i < rows; i++) {
            // isoXPrev = offset + i * offset * 2;
            // isoYPrev = offset;
            // isAbove = 0;
            for (int j = 0; j < collumn; j++) {
                double iso_x = 0;
                double iso_y = 0;
                double iso_z = 0;
                iso_x = j * (offset * 2) + (offset * (i % 2)) + offset * 2;
                if (!(i%2))
                    iso_y = (i + (i / 2)) * HEXAGONE_EDGE_LEN + HEXAGONE_EDGE_LEN * 2;
                else
                    iso_y = (i + ((i-1)/2)) * HEXAGONE_EDGE_LEN + HEXAGONE_EDGE_LEN / 2 + HEXAGONE_EDGE_LEN * 2;
                iso_z = 0;
                // isoXPrev = iso_x;
                // isoYPrev = iso_x;
                // isAbove
                // sfRectangleShape_setFillColor(rectangle, c);
                
                c.g = (i * (255 / rows));
                c.b = (j * (255 / collumn));
                /** old
                double iso_x = i * ((offset + 0.2) * 2) * cos(PI/3) + j * ((offset + 0.2) * 2) * cos(-PI/3) + MAX_Y / 2;
                double iso_y = i * ((offset + 0.2) * 2) * sin(PI/3) + j * ((offset + 0.2) * 2) * sin(-PI/3) + MAX_X / 2;
                double iso_z = (MAX_Y - j * offset * 0.5) * sin(ROTATION_ANGLE);
                // printf("%f\n", iso_z);
                */
                hexagoneSetColor(&hexagone, c);
                hexagoneSetPosition(&hexagone, (sfVector3f){iso_x, iso_y, iso_z});
                if (isPoint_insideHexagone(&hexagone, (sfVector2f){cursorPosition.x, cursorPosition.y}))
                    hexagoneSetColor(&hexagone, sfBlue);
                hexagoneDraw(window, &hexagone);
                // printf("%d %d %d %d\n", iso_x, iso_y, i, j);
                // sfRectangleShape_setPosition(rectangle, (sfVector2f){iso_x, iso_y});
                // sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
            }
            // isOffset++;
        }
        // for (int i = 0; i < HEXAGONE_TRIANGLE; i++) {
        //     sfRenderWindow_drawConvexShape(window,hexagone.triangle[i].shape, NULL);
        // }
        // sfRenderWindow_setView(window, view);
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
    }


}
