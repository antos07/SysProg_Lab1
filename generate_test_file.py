#! /usr/bin/python3.11

import string
from argparse import ArgumentParser, FileType
from random import randint, choices
from typing import TextIO

WORD_MAX_LENGTH = 30
JUNK_MAX_LENGTH = 1
JUNK_SYMBOLS = ''.join(set(chr(i) for i in range(1, 128)) - set(string.ascii_letters))


def generate(output_file: TextIO, alphabet: str, max_length: int) -> int:
    if max_length <= 0:
        return 0
    length = randint(1, max_length)
    text = ''.join(choices(alphabet, k=length))
    output_file.write(text)
    return length


def fill_file(output_file: TextIO, length: int) -> None:
    """Fills file with generated text"""
    length -= generate(output_file, JUNK_SYMBOLS, min(JUNK_MAX_LENGTH, length))
    while length > 0:
        length -= generate(output_file, string.ascii_letters, min(WORD_MAX_LENGTH, length))
        length -= generate(output_file, JUNK_SYMBOLS, min(JUNK_MAX_LENGTH, length))


def main():
    parser = ArgumentParser()
    parser.add_argument('length', type=int)
    parser.add_argument('output_file', type=FileType(mode='w', encoding='utf-8'))
    args = parser.parse_args()

    fill_file(args.output_file, args.length)

    args.output_file.close()


if __name__ == '__main__':
    main()
