
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include <stdlib.h>

int array_len(void *array)
{
    char **ptr = (char**)array;
    int i;

    for (i = 0; ptr[i]; i++);
    return i;
}

void init_array(void *array, int size)
{
    char **ptr = (char**)array;

    for (int i = 0; i < size ; i++)
        ptr[i] = NULL;
}

void free_array(void *array, int size)
{
    char **ptr = (char**)array;

    for (int i = 0; i < size && ptr[i]; i++)
        free(ptr[i]);
}

void push_back(struct list_s **list, void *data)
{
    struct list_s *new = malloc(sizeof(struct list_s));
    struct list_s *ptr = *list;

    new->next = NULL;
    new->ptr = data;
    if (!*list) {
        *list = new;
        return;
    }

    while (ptr->next)
        ptr = ptr->next;
    ptr->next = new;
}

void push_front(struct list_s **list, void *data)
{
    struct list_s *new = malloc(sizeof(struct list_s));
    struct list_s *ptr = *list;

    new->next = *list;
    new->ptr = data;
    *list = new;
}

void pop_back(struct list_s **list)
{
    struct list_s *ptr = *list;

    if (!*list || !ptr->next) {
        *list = NULL;
        return;
    }

    while (ptr->next && ptr->next->next)
        ptr = ptr->next;
    free(ptr->next->ptr);
    free(ptr->next);
    ptr->next = NULL;
}

void pop_front(struct list_s **list)
{
    struct list_s *ptr = *list;

    if (!*list)
        return;
    *list = (*list)->next;
    free(ptr->ptr);
    free(ptr);
}

void pop_address(struct list_s **list, void *address)
{
    struct list_s *ptr = *list;
    struct list_s *tmp = *list;

    if (!*list)
        return;
    while (ptr->next && ptr->next->ptr == address)
        ptr = ptr->next;
    if (ptr->next->ptr == address) {
        tmp = ptr->next;
        ptr->next = tmp->next;
        free(tmp->ptr);
        free(tmp);
    }
}

struct list_s *find_id(struct list_s *list, int id)
{
    while (list) {
        struct IResponse *request = (struct IResponse *)list->ptr;
        if (request->request_id == id)
            return list;
        list = list->next;
    }
    return list;
}