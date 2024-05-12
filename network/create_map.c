
#include "../include/map.h"
#include "../include/yaml.h"
#include <stdio.h>

void free_array(char **array)
{
    char **ptr = array;

    while (*array)
        free(*array++);
    free(ptr);
}

world_t *instanciate_file(char *file)
{
    world_t *world = malloc(sizeof(world_t));
    char **map = handle_file("./assets/map/scene1.yaml");
    grid_t scene = create_scene(map);
    tiles_t ***scene_object = create_scene_object(scene);
    
    free_array(free_array);
    world->map = scene_object;
    world->player_count = 0;
    memeset(&world->player, 0, sizeof(world->player));
    return world;
}