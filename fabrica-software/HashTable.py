INITIAL_CAPATY = 50

class Node: 
    def __init__(self, key, value) -> None:
        self.key = key
        self.value = value

class HashTable:
    def __init__(self) -> None:
        self.capacity = INITIAL_CAPATY
        self.size = 0 
        self.buckets = [None] * self.capacity

    def hash(self, key):
        hashsum = 0

        for idx, c in enumerate(key):
            hashsum += (idx + len(key)) ** ord(c)

        return hashsum % self.capacity

