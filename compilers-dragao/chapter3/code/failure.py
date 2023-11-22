#!/usr/bin/python3

"""
 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11
 0 | 1 | 0 | 1 | 2 | 0 | 1 | 2 | 3 | 4 | 5

 1  2  3  4  5  6  7  8  9  10 11
 A  A  B  A  A  C  A  A  B  A  A
             ^                 ^
"""


"""

[0, 0, 1, 2, 3, 1]

012345
ababaa
   ^

012345678
abababaab
     ^
"""

def kmp(a, pattern):
    n = len(pattern)
    pattern2 = "#" + pattern
    f = [0 for _ in range(n)]

    t = 0
    s = 1
    while s < n:
        while (t > 0 and pattern2[s+1] != pattern2[t+1]):
            t = f[t-1]

        if pattern2[s+1] == pattern2[t+1]:
            t += 1
            f[s] = t
        else:
            f[s] = 0

        s += 1

    s = 0
    i = 0
    while i < len(a):
        while (s > 0 and a[i] != pattern[s]):
            s = f[s-1]

        if a[i] == pattern[s]:
            s += 1

        if s == len(pattern):
            return True

        i += 1

    return False

# print(kmp("abababaab", "ababaa"))
# print(kmp("abababbaa", "ababaa"))
# print(kmp("abaabaa", "ababaa"))
# print(kmp("abababababaaa", "ababaa"))
# print(kmp("abababa", "ababaa"))
# print(kmp("ababababaaaba", "ababaa"))
print(kmp("abcabcabcabc", "abc"), " | Pattern appears at the beginning and repeats")    # Pattern appears at the beginning and repeats
print(kmp("aaaaaaa", "aa"), " | Pattern consists of repeated characters")          # Pattern consists of repeated characters
print(kmp("abcde", "xyz"), " | Pattern not present in the string")           # Pattern not present in the string
print(kmp("abcdeabcde", "cde"), " | Pattern appears at the end and repeats")      # Pattern appears at the end and repeats
print(kmp("abacabadabacaba", "aba"), " | Complex pattern repetition in the string") # Complex pattern repetition in the string
print(kmp("abcabcabcabc", "abcd"), " | Pattern not present in the string")   # Pattern not present in the string
print(kmp("abcabcabcabc", "abcabc"), " | Pattern appears at the beginning and repeats") # Pattern appears at the beginning and repeats
print(kmp("abracadabra", "abra"), " | Random pattern in a string with repetition")    # Random pattern in a string with repetition
