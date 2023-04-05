from ListaDinamica import ListaEncadeada
DIRECTORY_MAXIMUM_LENGTH = 256
SEGMENTS_MAXIMUM_LENGTH = 256


class Segment:

    def __init__(self) -> None:
        self.pointer_list = [ListaEncadeada()] * SEGMENTS_MAXIMUM_LENGTH 


class DinamicArray:

    def __init__(self) -> None:
        self.directory: list[Segment] = [None] * DIRECTORY_MAXIMUM_LENGTH



    