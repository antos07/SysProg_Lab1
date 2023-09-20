#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "words.h"
#include "word_map.h"

#define BUFFER_SIZE 256

bool is_word_char(char c) {
    return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}

void read_words_into_map(FILE *input_file, word_map_t *map) {
    char buffer[BUFFER_SIZE];
    word_t word;
    size_t chars_in_buffer, word_length = 0;
    while ((chars_in_buffer = fread(buffer, sizeof(char),
                                    sizeof(buffer), input_file))) {
        for (size_t i = 0; i < chars_in_buffer; ++i) {
            if (is_word_char(buffer[i])) {
                word[word_length] = buffer[i];
                ++word_length;

                if (word_length > WORD_SIZE) {
                    fprintf(stderr, "Too long word occurred!\n");
                    exit(EXIT_FAILURE);
                }
            } else if (word_length) {
                word[word_length] = '\0';
                insert_into_word_map(map, word);
                word_length = 0;
            }
        }
    }

    if (word_length) {
        word[word_length] = '\0';
        insert_into_word_map(map, word);
        word_length = 0;
    }
}

size_t find_max_word_distance(word_map_t *flat_map) {
    if (!flat_map) {
        return 0;
    }

    size_t max_distance = 0;

    tree_node_t *left_node = flat_map->root;
    while (left_node) {
        tree_node_t *right_node = left_node->right;
        while (right_node) {
            size_t distance = find_distance(left_node->word, right_node->word);
            if (distance > max_distance) {
                max_distance = distance;
            }
            right_node = right_node->right;
        }
        left_node = left_node->right;
    }

    return max_distance;
}

void print_words_with_distance(word_map_t *flat_map, size_t distance) {
    if (!flat_map) {
        return;
    }

    tree_node_t *left_node = flat_map->root;
    while (left_node) {
        tree_node_t *right_node = left_node->right;
        while (right_node) {
            if (find_distance(left_node->word, right_node->word) == distance) {
                printf("%s — %s\n", left_node->word, right_node->word);
            }
            right_node = right_node->right;
        }
        left_node = left_node->right;
    }
}

void process_file(FILE *input_file) {
    word_map_t *map = create_word_map();
    read_words_into_map(input_file, map);

    flatten_word_map(map);   // convert to linked list
    size_t max_distance = find_max_word_distance(map);

    if (max_distance == 0) {
        printf("Less than 2 unique words\n");
        return;
    }
    printf("Max distance between words: %ld.\nThe words with the max distance between them:\n", max_distance);
    print_words_with_distance(map, max_distance);

    clear_word_map(map);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to the input file>", argv[0]);
        return EXIT_FAILURE;
    }

    // Open file for read passed as the second arg
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    // Process file
    process_file(input_file);

    // Gracefully exit
    fclose(input_file);
    return EXIT_SUCCESS;
}
