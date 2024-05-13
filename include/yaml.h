
#ifndef YAML_H_
#define YAML_H_

typedef struct column_s {
    int value;
    int spawn;
} column_t;

typedef struct row_s {
    column_t **columns;
    int column_count;
} row_t;

typedef struct grid_s {
    row_t **rows;
    int row_count;
} grid_t;

grid_t create_scene(char **file);

#endif /* !YAML_H_ */
