//
// Created by antos07 on 9/20/23.
//

#ifndef SYSPROG_LAB1_STRING_MAP_H
#define SYSPROG_LAB1_STRING_MAP_H

#include <stdbool.h>
#include "words.h"

struct tree_node {
    word_t word;
    struct tree_node *left, *right;
};
typedef struct tree_node tree_node_t;

/*
 * A map of strings implemented as a binary search tree.
 */
struct word_map {
    tree_node_t *root;
};
typedef struct word_map word_map_t;

word_map_t *create_word_map(void);

void clear_word_map(word_map_t *map);

void insert_into_word_map(word_map_t *map, word_t word);

void flatten_word_map(word_map_t *map);

void print_word_map(word_map_t *map);

#endif //SYSPROG_LAB1_STRING_MAP_H
