# https://citeseerx.ist.psu.edu/doc/10.1.1.14.5908
# https://www.csd.uoc.gr/~hy460/pdf/Dynamic%20Hash%20Tables.pdf
# https://planetmath.org/goodhashtableprimes

from typing import Any
# from ListaDinamica import *

MINIMUN_SIZE = 256
DIRECTORY_MAXIMUM_LENGTH = 256
SEGMENTS_MAXIMUM_LENGTH = 256
PRIME = 104883
UPPER_BOUND = 5
LOWER_BOUND = 0


class Segment:

    def __init__(self) -> None:
        self.pointer_list = [None] * SEGMENTS_MAXIMUM_LENGTH

    def __getitem__(self, i: int):
        return self.pointer_list[i]

    def __setitem__(self, i: int, value: Any):
        self.pointer_list[i] = value


class Node:
    def __init__(self, key, value) -> None:
        self.value: Any = value
        self.key: str = key
        self.next: Node | None = None 


class HashTable:

    def __init__(self) -> None:
        self.doubled: int = 0  # L
        self.next_bucket: int = 0  # p
        self.length: int = 0
        self.upper_bound: int = UPPER_BOUND
        self.lower_bound: int = LOWER_BOUND
        self.directory: list[Segment] = [Segment()] + [None] * (DIRECTORY_MAXIMUM_LENGTH - 1)
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
    
    def find_head(self, key: str) -> Node:
        addr: int = self.address(key)
        current_segment: Segment = self.directory[addr //
                                                  SEGMENTS_MAXIMUM_LENGTH]
        segment_i: int = addr % DIRECTORY_MAXIMUM_LENGTH
        return current_segment[segment_i]

    def find(self, key: str) -> Any:
        current_node: Node = self.find_head(key)
        while current_node != None:
            if current_node.key == key:
                return current_node.value
            current_node = current_node.next
        
    def remove(self, key: str) -> None:
        current_node: Node = self.find_head(key)

        # if current_node.key == key:
        #     if current_node.next != None:
        #         current_node.next 

        while current_node.next != None:
            if current_node.next.key == key:
                current_node.next = current_node.next.next
            current_node = current_node.next

        self.length -= 1
        self.keys.remove(key)
        if self.length / self.maxp < self.lower_bound:
            self.shrink_table()
    
    def shrink(self) -> None:
        self.next_bucket -= 1
        if self.next_bucket < 0:
            self.doubled -= 1
            self.maxp = MINIMUN_SIZE * 2**self.doubled
            self.next_bucket = self.maxp

    def insert(self, key: str, value: Any) -> None:
        if self.length / self.maxp > self.upper_bound:
            self.expand_table()

        new_node: Node = Node(key, value)

        addr = self.address(key)

        current_segment: Segment = self.directory[addr//SEGMENTS_MAXIMUM_LENGTH]
        segment_i: int = addr % DIRECTORY_MAXIMUM_LENGTH
        current_node: Node | None = current_segment[segment_i]

        if current_node == None:
            current_segment[segment_i] = new_node
        else:
            while current_node.next != None:
                current_node = current_node.next
            current_node.next = new_node
        
        self.keys.append(key)
        self.length += 1

    def new_segment(self, i: int) -> None:
        self.directory[i] = Segment()

    def get_keys(self):
        return self.keys

    def shrink_table():
        pass

    # TODO Aqui tem mt problema
    def expand_table(self):
        if self.maxp + self.next_bucket < DIRECTORY_MAXIMUM_LENGTH * SEGMENTS_MAXIMUM_LENGTH:

            new_addr: int = self.maxp + self.next_bucket

            directory_i = new_addr // SEGMENTS_MAXIMUM_LENGTH
            if new_addr % SEGMENTS_MAXIMUM_LENGTH == 0:
                self.new_segment(directory_i)

            new_segment: Segment = self.directory[directory_i]
            new_segment_i: int = new_addr % SEGMENTS_MAXIMUM_LENGTH


            old_segment: Segment = self.directory[self.next_bucket//SEGMENTS_MAXIMUM_LENGTH]
            old_segment_i: int = self.next_bucket % SEGMENTS_MAXIMUM_LENGTH

            self.resize()

            # current_b: Bucket = 

            # current_n: Node = current_b.head
            current_n: Node = old_segment[old_segment_i]
            new_segment[new_segment_i]: Node | None = None
            previous: Node | None = None
            last_of_new: Node | None = None

            while current_n != None:

                if self.address(current_n.key) == new_addr:

                    if last_of_new == None:
                        new_segment[new_segment_i] = current_n
                    else:
                        last_of_new.next = current_n

                    if previous == None:
                        old_segment[old_segment_i] = current_n.next
                    else:
                        previous.next = current_n.next

                    last_of_new = current_n
                    current_n = current_n.next
                    last_of_new.next = None
                else:
                    previous = current_n
                    current_n = current_n.next

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
    