import unittest
from HashTable import * 
from random import randint, choice
from config import *
from TesteFuncUtils import *
import numpy as np

class TestePerfomanceHashTable(unittest.TestCase):
    
    def setUp(self) -> None:
        self.hash_table = HashTable()
        for _ in range(AMOUNT_OF_TST_CASES):
            self.hash_table.insert(make_rand_str(LENGTH_RAND_STR), randint(0, 10))
        self.keys = self.hash_table.get_keys()

    @time_it
    def test_insert_speed(self):
        self.hash_teste = HashTable()
        for _ in range(AMOUNT_OF_TST_CASES):
            self.hash_teste.insert(make_rand_str(LENGTH_RAND_STR), randint(0, 10))

    @time_it
    def test_find_speed(self):
        for _ in range(AMOUNT_OF_TST_CASES):
            self.hash_table.find(choice(self.keys))

    @time_it
    def test_remove_speed(self):
        for key in self.hash_table.get_keys():
            self.hash_table.remove(key)             
    
    @time_it
    def test_hash_time(self):
        for _ in range(AMOUNT_OF_TST_CASES):
            self.hash_table.hash(make_rand_str(LENGTH_RAND_STR))
    
    def test_collision(self):
        list_of_collisions = []
        for nodes in self.hash_table.buckets:
            if nodes is not None:
                len_node = len(nodes.list)
                list_of_collisions.append(len_node) 

        list_of_collisions.sort()
        print('distribution:')
        print(f'Maximun => {max(list_of_collisions)}')
        print(f'Minimun => {min(list_of_collisions)}')
        print(f'Median  => {np.median(list_of_collisions)}')  
        print(f'Average => {np.average(list_of_collisions)}', end='\n\n')  


if __name__ == '__main__':
    unittest.main()