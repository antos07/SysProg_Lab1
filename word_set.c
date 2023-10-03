//
// Created by antos07 on 9/20/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "word_set.h"

word_set_t *create_word_set(void) {
    word_set_t *set = (word_set_t *) malloc(sizeof(word_set_t));
    if (!set) {
        fprintf(stderr, "Failed to allocate memory!");
        exit(EXIT_FAILURE);
    }
    set->root = NULL;
    return set;
}

static void delete_tree(tree_node_t *root) {
    if (!root) {
        return;
    }

    // Delete subtrees.
    delete_tree(root->left);
    delete_tree(root->right);

    free(root);
}

void clear_word_set(word_set_t *set) {
    if (!set) {
        return;
    }
    delete_tree(set->root);
    free(set);
}

static tree_node_t *create_tree_node(word_t word) {
    tree_node_t *node = (tree_node_t *) malloc(sizeof(tree_node_t));
    if (!node) {
        fprintf(stderr, "Failed to allocate memory!");
        exit(EXIT_FAILURE);
    }
    strncpy(node->word, word, WORD_SIZE);
    node->left = NULL;
    node->right = NULL;
    return node;
}

static tree_node_t *insert_into_tree(tree_node_t *root, word_t word) {
    if (!root) {
        return create_tree_node(word);
    }

    int ret = compare_words(word, root->word);
    switch (ret) {
        case -1: {
            root->left = insert_into_tree(root->left, word);
            break;
        }
        case 1: {
            root->right = insert_into_tree(root->right, word);
            break;
        }
        default: // 0
            break;
    }
    return root;
}

void insert_into_word_set(word_set_t *set, word_t word) {
    if (!set) {
        return;
    }
    set->root = insert_into_tree(set->root, word);
}

static tree_node_t *flatten_tree(tree_node_t *root) {
    if (!root) {
        return NULL;
    }

    root->left = flatten_tree(root->left);
    root->right = flatten_tree(root->right);

    if (!root->left) return root;

    tree_node_t *tmp = root->left;
    while (tmp->right) {
        tmp = tmp->right;
    }

    tmp->right = root;
    root = root->left;
    tmp->right->left = NULL;
    return root;
}

void flatten_word_set(word_set_t *set) {
    set->root = flatten_tree(set->root);
}

void print_tree(tree_node_t *root) {
    if (!root) {
        return;
    }

    print_tree(root->left);
    printf("%s\n", root->word);
    print_tree(root->right);
}

void print_word_set(word_set_t *set) {
    if (set) {
        print_tree(set->root);
    }
}
