#!/usr/bin/python3

def merge_the_tools(string: str, k: int):
    collected_string = []
    for i in range(0, len(string), k):
        t = string[0+i:k+i]
        u = ""
        for c in t:
            if c not in u: u+=c
        collected_string.append(u)

    for u in collected_string: print(u)

if __name__ == '__main__':
    # string, k = input(), int(input())
    string = 'AAABCADDE'
    k = 3
    merge_the_tools(string, k)
    string = 'AABCAAADA'
    k = 3
    merge_the_tools(string, k)