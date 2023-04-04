import unittest
from HashTable import * 
from random import randint, choice
import string
AMOUT_OF_TST_CASES = 1_00
LENGTH_RAND_STR = 10

def make_rand_str(length):
    return ''.join(choice(string.ascii_letters) for _ in range(length))

class TesteHashTable(unittest.TestCase):
    def setUp(self):
        self.hash_table = HashTable()
        self.hash_table.insert("apple", 5)
        self.hash_table.insert("orange", 50)
        self.hash_table.insert("batata", 10)

    def test_insert(self):
        self.hash_table.insert("dog", 7)
        self.assertEqual(self.hash_table.find("dog"), 7)

    def test_delete(self):
        self.hash_table.remove("apple")
        self.assertIsNone(self.hash_table.find("apple"))
        self.assertEqual(self.hash_table.find("orange"), 50)
    
    def test_resize(self):
        len1 = len(self.hash_table)
        self.hash_table.insert("papel", 3)
        len2 = len(self.hash_table)
        self.assertEqual(len1+1, len2)

    def test_collision(self):
        count = 0
        for _ in range(AMOUT_OF_TST_CASES):
            self.hash_table.insert(make_rand_str(LENGTH_RAND_STR), randint(0, 10))

        for nodes in self.hash_table.buckets:
            if nodes is not None and len(nodes.list) > 1:
                count += len(nodes.list) - 1                

        print(f'{count} COLLISIONS FOR {AMOUT_OF_TST_CASES} INSERTS')

    def test_iterator(self):
        with self.assertRaises(TypeError) as cm:
            for _ in self.hash_table:
                pass
        
        self.assertTrue(TypeError in cm.exception)
    


if __name__ == '__main__':
    unittest.main()    

