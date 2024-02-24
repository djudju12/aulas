#!/usr/bin/python3

"""
You are given  words. Some words may repeat.
For each word, output its number of occurrences.
The output order should correspond with the
input order of appearance of the word.
See the sample input/output for clarification.
"""

def main():
    n = int(input())
    words = {}
    for _ in range(n):
        w = input()
        if words.get(w) is None: words[w] = 1
        else: words[w] += 1

    print(len(words))
    [print(n, end=" ") for n in words.values()]


if __name__ == '__main__':
    main()