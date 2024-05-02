#include <SFML/Graphics/RenderWindow.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/read.h"
#include "include/window.h"
#include "include/map.h"
#include "include/yaml.h"



sfVector2i get_spawn_position(void *origin)
{
    char **map = origin;
    int y, x;

    for (y = 0; map[y]; y++)
        for (x = 0; map[y][x]; x++)
            if (map[y][x] == PLAYER + '0')
                return (sfVector2i){x, y};
    perror("no player");
    exit(EXIT_FAILURE);

}

size_t array_len(void *array)
{
    int i;
    char *ptr = array;

    for (i = 0; ptr[i]; i++);
    return i;
}

tiles_t **create_map(char **content_file)
{
    //TODO api ?
    sfVector2i player_position = get_spawn_position(content_file);



}

int main()
{
    char **map = handle_file("./assets/map/scene1.yaml");
    grid_t scene = create_scene(map);
    tiles_t ***scene_object = create_scene_object(scene);

    sfVideoMode mode = {WIDTH, HEIGHT, BITSPERPIXEL};
    sfRenderWindow* window;
    sfEvent event;
    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    /* Load a sprite to display */
    
    
    sfRenderWindow_setFramerateLimit(window, FRAMERATELIMIT);

    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        for (int i = 0; scene_object[i]; i++)
            for (int j = 0; scene_object[i][j]; j++)
                scene_object[i][j]->print(scene_object[i][j], window);
        /* Clear the screen */
        /* Update the window */
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
    }
    /* Cleanup resources */
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
