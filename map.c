#include "include/map.h"
#include "include/yaml.h"
#include <stdlib.h>
#include <stddef.h>


tiles_t ***create_scene_object(grid_t *scene)
{
    tiles_t *(*backgroundConstructor[]) (sfVector2f) = {
        &create_ground, //TODO create the void finction
        &create_wall,
        &create_ground
    };
    tiles_t ***scene_object = malloc(sizeof(tiles_t**) * (scene->row_count + 1));
    sfVector2f pos = {0, 0};
    int i = 0;
    int j = 0;
    
    for (i = 0; i != scene->row_count; i++) {
        pos.x = 0;
        scene_object[i] = malloc(sizeof(tiles_t*) * (scene->rows[i]->column_count + 1));
        for (j = 0; j != scene->rows[i]->column_count; ++j) {
            scene_object[i][j] = backgroundConstructor[scene->rows[i]->columns[j]->value](pos);
            pos.x += 50;
            if (scene->rows[i]->columns[j]->spawn) {
                scene_object[i][j]->spawn = scene->rows[i]->columns[j]->spawn;
                // printf("je suis la %f %f\n", scene_object[i][j]->position.x, scene_object[i][j]->position.y);
                
            }
        }
        scene_object[i][j] = NULL;
        pos.y += 50;
    }
    scene_object[i] = NULL;

    return scene_object;
}