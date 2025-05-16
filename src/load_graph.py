from typing import List, Dict

def load_graph(filename: str) -> Dict[int, List[int]]:
    with open(filename) as file:
        line: str = file.readline()

        #скипаем комментарии
        while line and line[0] == "#":
            line = file.readline()

        graph: Dict[int, List[int]] = {}
        while line:
            vertexes = line.split(" ")

            if len(vertexes) != 2:
                return {}

            v1, v2 = int(vertexes[0]), int(vertexes[1])
            append_edge_into_graph(graph, v1, v2)
            append_edge_into_graph(graph, v2, v1)

            line = file.readline()

        return graph


def append_edge_into_graph(graph: Dict[int, List[int]], from_: int, to_: int) -> None:

    if from_ in graph:
        graph[from_].append(to_)
    else:
        graph[from_] = [to_]