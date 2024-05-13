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
    while (**file && !strncmp(**file, "        ", strlen("        "))) {
        if (!strncmp(**file, "        value", strlen("        value"))) {
            column->value = atoi((**file) + strlen("        value: "));
        }
        if (!strncmp(**file, "        spwan", strlen("        value"))) {
            column->spawn = atoi((**file) + strlen("        spawn: "));
        }
        if (**file)
            (*file)++;
    }
    return column;
}

row_t *create_row(char ***file) {
    row_t *row =  malloc(sizeof(row_t));

    row->columns = NULL;
    row->column_count = 0;
    (*file)++;
    while (**file && !strncmp(**file, "    ", strlen("    "))) {
        if (!strncmp(**file, "    columns", strlen("    columns"))) {
            (*file)++;
            while (**file && !strncmp(**file, "      ", strlen("      "))) {
                row->column_count++;
                row->columns = realloc(row->columns, sizeof(column_t*) * (row->column_count));
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
    }
    printf("\n%d\n", scene.row_count);
    return scene;
}