import unittest
from random import choice
import string
from config import *
from HashTable import * 
from config import *

class TesteHashTable(unittest.TestCase):
    def setUp(self):
        self.hash_table = HashTable()
        self.hash_table.insert("apple", 5)
        self.hash_table.insert("orange", 50)
        self.hash_table.insert("batata", 10)

    def test_insert(self):
        self.hash_table.insert("dog", 7)
        self.assertEqual(self.hash_table.find("dog"), 7)
        print("Insert OK")

    def test_delete(self):
        self.hash_table.remove("apple")
        self.assertIsNone(self.hash_table.find("apple"))
        self.assertEqual(self.hash_table.find("orange"), 50)
        print("Delete OK")

    def test_resize(self):
        len1 = len(self.hash_table)
        self.hash_table.insert("papel", 3)
        len2 = len(self.hash_table)
        self.assertEqual(len1+1, len2)
        print("Resize OK")

    def test_find(self):
        value = self.hash_table.find("batata")
        self.assertAlmostEqual(value, 10)
        print("Find OK")
    
    def test_get_keys(self):
        self.assertTrue("batata" in self.hash_table.get_keys())
        print("Get keys OK")


if __name__ == '__main__':
    unittest.main()    

