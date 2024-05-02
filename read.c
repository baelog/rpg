#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int count_char(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    printf("%d\n", count);
    return count;
}

char **create_array(char str[])
{
    char **array = malloc(sizeof(char*) * (count_char(str, '\n') + 2));
    char **ptr = array;
    
    *ptr = strtok(str, "\n");
    while (*ptr) {
        ++ptr;
        char *tmp = strtok(NULL, "\n");
        *ptr = tmp ? strdup(tmp) : NULL;
    }
    return array;
}

__off_t file_size(char *file)
{
    struct stat st;
    int stat_ret = stat(file, &st);

    if (stat_ret < 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    return st.st_size;
}

void read_file(char *file, char *buffer, __off_t size) {
    int fd;
    int rd;

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    rd = read(fd, buffer, size);
    if (rd < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[rd] = '\0';
}

char **handle_file(char *file)
{
    __off_t size = file_size(file);
    char buffer[size];

    read_file(file, buffer, size);
    // write(1, buffer, strlen(buffer));
    return create_array(buffer);
}
