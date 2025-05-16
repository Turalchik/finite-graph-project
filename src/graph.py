class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, from_: int, to_: int):
        if from_ in self.graph:
            self.graph[from_].append(to_)
        else:
            self.graph[from_] = [to_]

    def __str__(self):
        return str(self.graph)