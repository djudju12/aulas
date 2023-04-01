from typing import Any
from ListaDinamicaMelhorada import *

INITIAL_CAPATY = 50
class NodeHash:
    def __init__(self, key: str, valor: Any) -> None:
        self.value: Any = valor 
        self.key: str = key 

    def __eq__(self, other: 'NodeHash'):
        if isinstance(other, NodeHash):
            return (other.value == self.value and other.key == self.key)
        return False

class Nodes: 
    def __init__(self, node: NodeHash) -> None:
        self.list: ListaEncadeada = ListaEncadeada()
        self.list.append(node)


class HashTable:
    def __init__(self) -> None:
        self.capacity: int = INITIAL_CAPATY
        self.size: int = 0 
        self.buckets: list[Nodes] = [None] * self.capacity

    def hash(self, key) -> int:
        hashsum: int = 0

        for idx, c in enumerate(key):
            hashsum += (idx + len(key)) ** ord(c)
            hashsum = hashsum % self.capacity 
        return hashsum

    def print_hash(self):
        print("{ ", end="")
        for nodes in self.buckets:
            if nodes is not None:
                for node in nodes.list:
                    print(f"'{node.key}' -> {node.value}", end=" ")
        print("}", end="")

    def insert(self, key, value):
        self.size += 1 
        index: int = self.hash(key)
        nodes: Nodes = self.buckets[index]
        node: NodeHash = NodeHash(key, value)

        if nodes is None:
            self.buckets[index] = Nodes(node)
            return 

        nodes.list.append(node)

    def find(self, key) -> Any:
        index: int = self.hash(key)
        nodes: Nodes = self.buckets[index]

        if nodes is None:
            return None 
        
        for node in nodes.list:
            if node.key == key:
                return node.value  

        
    def remove(self, key) -> None:
        index: int = self.hash(key)
        nodes: Nodes = self.buckets[index]
        
        if nodes is None: 
            return None 

        for node in nodes.list:
            if node.key == key:
                nodes.list.first_ocurrence(node)



if __name__ == '__main__':
    hash1 = HashTable()
    hash1.insert("a", 1)
    hash1.insert("b", 2)
    hash1.insert("c", 2)
    hash1.print_hash()

