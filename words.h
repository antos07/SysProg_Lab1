//
// Created by antos07 on 9/20/23.
//

#ifndef SYSPROG_LAB1_WORDS_H
#define SYSPROG_LAB1_WORDS_H

#define WORD_SIZE 30
typedef char word_t[WORD_SIZE + 1];

int compare_words(const word_t w1, const word_t w2);

size_t find_distance(const word_t w1, const word_t w2);

#endif //SYSPROG_LAB1_WORDS_H
