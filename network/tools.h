
#ifndef TOOLS_H_
#define TOOLS_H_

struct IResponse {
    int len;
    int type;
    int request_id;
    char *body;
};

struct list_s {
    struct IResponse *ptr;
    struct list_s *next;
};

typedef struct request_s request_t;

void free_array(void *array, int size);
int array_len(void *array);
void init_array(void *array, int size);
void push_back(struct list_s **list, void *data);
void push_front(struct list_s **list, void *data);
void pop_back(struct list_s **list);
void pop_front(struct list_s **list);
void pop_address(struct list_s **list, void *address);
struct list_s *find_id(struct list_s *list, int id);

#endif /* !TOOLS_H_ */
