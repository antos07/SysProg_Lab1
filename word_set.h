//
// Created by antos07 on 9/20/23.
//

#ifndef SYSPROG_LAB1_STRING_set_H
#define SYSPROG_LAB1_STRING_set_H

#include <stdbool.h>
#include "words.h"

struct tree_node {
    word_t word;
    struct tree_node *left, *right;
};
typedef struct tree_node tree_node_t;

/*
 * A set of strings implemented as a binary search tree.
 */
struct word_set {
    tree_node_t *root;
};
typedef struct word_set word_set_t;

word_set_t *create_word_set(void);

void clear_word_set(word_set_t *set);

void insert_into_word_set(word_set_t *set, word_t word);

void flatten_word_set(word_set_t *set);

void print_word_set(word_set_t *set);

#endif //SYSPROG_LAB1_STRING_set_H
