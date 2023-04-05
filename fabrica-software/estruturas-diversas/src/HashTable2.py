# https://citeseerx.ist.psu.edu/doc/10.1.1.14.5908
# https://www.csd.uoc.gr/~hy460/pdf/Dynamic%20Hash%20Tables.pdf
# https://planetmath.org/goodhashtableprimes

from typing import Any
from ListaDinamica import *

MINIMUN_SIZE = 256
DIRECTORY_MAXIMUM_LENGTH = 256
SEGMENTS_MAXIMUM_LENGTH = 256
PRIME = 104883
UPPER_BOUND = 5
LOWER_BOUND = 0


class Segment:

    def __init__(self) -> None:
        self.pointer_list = [ListaEncadeada()] * SEGMENTS_MAXIMUM_LENGTH

    def __getitem__(self, i: int):
        return self.pointer_list[i]

    def __setitem__(self, i: int, value: Any):
        self.pointer_list[i] = value


class HashTable:

    def __init__(self) -> None:
        self.doubled: int = 0  # L
        self.next_bucket: int = 0  # p
        self.length: int = 0
        self.upper_bound: int = UPPER_BOUND
        self.lower_bound: int = LOWER_BOUND
        self.directory: list[Segment] = [Segment()]
        self.maxp = MINIMUN_SIZE * 2**self.doubled
        self.keys: list[str] = []

    def __len__(self) -> int:
        return self.length

    @staticmethod
    def str2int(string: str) -> int:
        string = string.encode('ascii')
        return int.from_bytes(string, byteorder='big')

    def address(self, key: str) -> int:
        key = self.str2int(key)
        h: int = key % PRIME
        addr: int = h % self.maxp
        if addr < self.next_bucket:
            addr = h % (self.maxp * 2)
        return addr

    def shrink(self) -> None:
        self.next_bucket -= 1
        if self.next_bucket < 0:
            self.doubled -= 1
            self.maxp = MINIMUN_SIZE * 2**self.doubled
            self.next_bucket = self.maxp

    def find_first(self, key: str) -> ListaEncadeada:
        addr: int = self.address(key)
        current_segment: Segment = self.directory[addr //
                                                  SEGMENTS_MAXIMUM_LENGTH]
        segment_i: int = addr % DIRECTORY_MAXIMUM_LENGTH
        return current_segment[segment_i]

    def find(self, key: str) -> Any:
        chain: ListaEncadeada = self.find_first(key)

        for k, v in chain:
            if k == key:
                return v
            else:
                None

    def remove(self, key: str) -> None:
        chain: ListaEncadeada = self.find_first(key)

        for k, v in chain:
            if k == key:
                # Nãos sei pq mas ele faz isso duas vezes se não colocar o break
                chain.first_ocurrence((k, v))
                break

        self.length -= 1
        self.keys.remove(key)
        if self.length / self.maxp < self.lower_bound:
            self.shrink_table()

    def insert(self, key: str, value: any) -> None:
        if self.length / self.maxp > self.upper_bound:
            self.expand_table()
        chain: ListaEncadeada = self.find_first(key)
        chain.append((key, value))
        self.keys.append(key)
        self.length += 1

    def new_segment(self) -> None:
        self.directory.append(Segment())

    def get_keys(self):
        return self.keys

    def shrink_table():
        pass

    # TODO Aqui tem mt problema
    def expand_table(self):
        if self.maxp + self.next_bucket < DIRECTORY_MAXIMUM_LENGTH * SEGMENTS_MAXIMUM_LENGTH:
            old_segment: Segment = self.directory[self.next_bucket //
                                                  SEGMENTS_MAXIMUM_LENGTH]
            old_segment_i: int = self.next_bucket % SEGMENTS_MAXIMUM_LENGTH
            new_addr: int = self.maxp + self.next_bucket

            if new_addr % SEGMENTS_MAXIMUM_LENGTH == 0:
                self.new_segment()

            new_segment: Segment = self.directory[new_addr //
                                                  SEGMENTS_MAXIMUM_LENGTH]
            new_segment_i: int = new_addr % SEGMENTS_MAXIMUM_LENGTH

            self.resize()

            current: Node = old_segment[old_segment_i].primeiro
            previous: Node = None
            last_of_new: Node = None
            new_segment[new_segment_i] = None
            while current != None:
                if self.address(current.value[0]) == new_addr:

                    if last_of_new == None:
                        new_segment[new_segment_i] = current
                    else:
                        last_of_new.proximo = current

                    if previous == None:
                        old_segment[old_segment_i] = current.proximo
                    else:
                        previous.proximo = current.proximo

                    last_of_new = current
                    current = current.proximo
                    last_of_new.proximo = None
                else:
                    previous = current
                    current = current.proximo

    def resize(self) -> None:
        self.next_bucket += 1
        if self.next_bucket == self.maxp:
            self.doubled += 1
            self.maxp = MINIMUN_SIZE * 2**self.doubled
            self.next_bucket = 0


if __name__ == '__main__':
    from TesteFuncUtils import make_rand_str
    from config import LENGTH_RAND_STR
    hash_table = HashTable()
    for _ in range(SEGMENTS_MAXIMUM_LENGTH*(UPPER_BOUND+1)):
        hash_table.insert(make_rand_str(LENGTH_RAND_STR), 1)
    