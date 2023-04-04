import unittest
from HashTable import * 
from random import randint, choice
from functools import wraps
import timeit
import string

AMOUT_OF_EXECS = 1_0
AMOUT_OF_TST_CASES = 1_000
LENGTH_RAND_STR = 10

def make_rand_str(length):
    return ''.join(choice(string.ascii_letters) for _ in range(length))


def time_it(func):
    @wraps(func)
    def timeit_wrapper(*args, **kwargs):
        t = timeit.timeit(lambda: func(*args, **kwargs), number=AMOUT_OF_TST_CASES)
        print(f'Func => {func.__name__}\nTime => {t}\nFor {AMOUT_OF_TST_CASES} executions')
        return 
    return timeit_wrapper

class TestePerfomanceHashTable(unittest.TestCase):

    @time_it
    def test_insert_speed(self):
        self.hash_table = HashTable()
        for _ in range(AMOUT_OF_TST_CASES):
            self.hash_table.insert(make_rand_str(LENGTH_RAND_STR), randint(0, 10))

    @time_it
    def test_remove_speed(self):
        for key in self.hash_table:
            self.hash_table.remove(key)             

if __name__ == '__main__':
    unittest.main()