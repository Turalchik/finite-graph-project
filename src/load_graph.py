from typing import List, Dict
from src.graph import Graph


def load_undirected_graph(filename: str) -> Graph:
    with open(filename) as file:
        line: str = file.readline()

        #скипаем комментарии
        while line and line[0] == "#":
            line = file.readline()

        graph: Graph = Graph()
        while line:
            vertexes = line.split(" ")

            if len(vertexes) != 2:
                return None

            v1, v2 = int(vertexes[0]), int(vertexes[1])
            graph.add_edge(v1, v2)
            graph.add_edge(v2, v1)

            line = file.readline()

        return graph
