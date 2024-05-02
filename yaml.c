#include "include/yaml.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

column_t *create_column(char ***file) {
    column_t *column = malloc(sizeof(column_t));
    column->value = 0;
    column->spawn = 0;

    (*file)++;

    // write(1, **file, strlen(**file));
    // write(1, "fuck3\n", strlen("fuck3\n"));
    while (**file && !strncmp(**file, "        ", strlen("        "))) {
        if (!strncmp(**file, "        value", strlen("        value"))) {
            column->value = atoi((**file) + strlen("        value: "));
        //    write(1, "taking value\n", strlen("taking value\n"));

            // (*file)++;
        }
        if (!strncmp(**file, "        swpan", strlen("        value"))) {
            column->spawn = atoi((**file) + strlen("        spawn: "));
        //    write(1, "taking value\n", strlen("taking value\n"));

            // (*file)++;
        }
        // write(1, "\n test1 \n", strlen("\n test1 \n"));
        // write(1, **file, strlen(**file));
        // write(1, "\n test2 \n", strlen("\n test2 \n"));
        if (**file)
            (*file)++;
    }
    // if (**file)
    //     (*file)++;
    return column;
}

row_t *create_row(char ***file) {
    row_t *row =  malloc(sizeof(row_t));

    row->columns = NULL;
    row->column_count = 0;
    // write(1, **file, strlen(**file));
    (*file)++;
    // write(1, **file, strlen(**file));
    // write(1, "fuck\n", strlen("fuck\n"));
    while (**file && !strncmp(**file, "    ", strlen("    "))) {
        if (!strncmp(**file, "    columns", strlen("    columns"))) {
            (*file)++;
            while (**file && !strncmp(**file, "      ", strlen("      "))) {
                row->column_count++;
                row->columns = realloc(row->columns, sizeof(column_t*) * (row->column_count));
                // if(!row->columns)
                //     write(1, "fuck\n", strlen("fuck\n"));
                printf("\n col= %d\n", row->column_count);
                
                row->columns[row->column_count - 1] = create_column(file);
            }
            if(**file)
                (*file)--;
        }
        if(**file)
            (*file)++;
    }
    return row;
}

grid_t create_scene(char **file) {
    char **ptr = file;
    grid_t scene;

    scene.row_count = 0;
    scene.rows = NULL;
    ptr++;
    while (*ptr) {
        scene.rows = realloc(scene.rows, sizeof(row_t*) * (scene.row_count + 1));

        scene.rows[scene.row_count] = create_row(&ptr);
        scene.row_count++;
        // if (*ptr)
        //     ptr++;
    }
    printf("\n%d\n", scene.row_count);
    return scene;
}