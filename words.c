//
// Created by antos07 on 9/20/23.
//

#include <string.h>
#include "words.h"

// Returns 0 if w1 == w2, -1 if w1 < w2, 1 if w1 > w2
int compare_words(const word_t w1, const word_t w2) {
    int ret = strncmp(w1, w2, WORD_SIZE);
    if (ret < 0) {
        return -1;
    } else if (ret > 0) {
        return 1;
    }
    return 0;
}

size_t find_distance(const word_t w1, const word_t w2) {
    if (!w1) {
        return strlen(w2);
    }
    if (!w2) {
        return strlen(w1);
    }
    size_t distance = 0;
    for (size_t i = 0; i <= WORD_SIZE; ++i) {
        distance += (w1[i] != w2[i]);
    }
    return distance;
}


