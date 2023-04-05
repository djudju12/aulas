# https://citeseerx.ist.psu.edu/doc/10.1.1.14.5908
# https://www.csd.uoc.gr/~hy460/pdf/Dynamic%20Hash%20Tables.pdf
# https://planetmath.org/goodhashtableprimes

from typing import Any
from ListaDinamica import *

MINIMUN_SIZE = 50
DIRECTORY_MAXIMUM_LENGTH = 256
SEGMENTS_MAXIMUM_LENGTH = 256
PRIME = 104883


class Segment:

    def __init__(self) -> None:
        self.pointer_list = [ListaEncadeada()] * SEGMENTS_MAXIMUM_LENGTH 


class HashTable:


    def __init__(self) -> None:
        self.doubled: int = 0 # L
        self.next_bucket: int = 0 # p 
        self.length: int = 0
        self.upper_bound: int = 0
        self.lower_bound: int = 0
        self.directory: list[Segment] = None
        self.maxp = MINIMUN_SIZE 
    
    @staticmethod
    def _str2int(string: str) -> int:
        string = string.encode('ascii')
        return int.from_bytes(string, byteorder='big')

    def _hash(self, key: str) -> int:
        key = self._str2int(key)
        h: int = key % PRIME
        addr: int = h % self.maxp  
        if addr < self.next_bucket:
            addr = h % (self.maxp * 2)
        return addr

    def _resize(self) -> None:
        self.next_bucket += 1
        if self.next_bucket == self.maxp:
            self.doubled += 1
            self.maxp = MINIMUN_SIZE * 2**self.doubled
            self.next_bucket = 0

    def _shrink(self) -> None:
        self.next_bucket -= 1
        if self.next_bucket < 0:
            self.doubled -= 1
            self.maxp = MINIMUN_SIZE * 2**self.doubled 
            self.next_bucket = self.maxp

    def _address(self, key: str) -> int:
        addr: int = self._hash(key, self.next_bucket)
        if addr < self.next_bucket:
            addr = self._hash(key, self.next_bucket + 1)
