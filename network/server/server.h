/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

enum type {
    BROADDCAST,
    ID,
    INVENTARY,
    ACTIONS
};

struct resquest_s {
    int len;
    int type;
    char *data;
} request_t;

#endif /* !SERVER_H_ */
