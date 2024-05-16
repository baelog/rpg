
#ifndef TOOLS_H_
#define TOOLS_H_

struct list_s {
    void *ptr;
    struct list_s *next;
};

void free_array(void *array, int size);
int array_len(void *array);
void init_array(void *array, int size);
void push_back(struct list_s **list, void *data);
void push_front(struct list_s **list, void *data);
void pop_back(struct list_s **list);
void pop_front(struct list_s **list);
void pop_address(struct list_s **list, void *address);

#endif /* !TOOLS_H_ */
