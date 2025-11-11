import random
import sys

def generate_weakly_connected_digraph(N, P=0):
    """
    Генерирует слабо-связанный ориентированный граф с N вершинами.
    P - коэффициент разреженности [0..1]:
        P=0 - минимальное число ребер для связанности (N-1)
        P=1 - максимально насыщенный граф (N*(N-1) ребер)
    """
    if N < 1:
        return []
    
    edges = []
    vertices = list(range(N))
    random.shuffle(vertices)
    connected = {vertices[0]}
    remaining = set(vertices[1:])

    # Создать остов (неориентированный)
    while remaining:
        u = random.choice(tuple(connected))
        v = random.choice(tuple(remaining))
        edges.append((u, v))
        connected.add(v)
        remaining.remove(v)

    # Ориентировать ребра остова
    oriented_edges = []
    for (u, v) in edges:
        if random.choice([True, False]):
            oriented_edges.append((u, v))
        else:
            oriented_edges.append((v, u))

    max_edges = N * (N - 1)
    min_edges = N - 1
    additional_edges_count = int(P * (max_edges - min_edges))

    existing = set(oriented_edges)

    # Добавить дополнительные ребра, чтобы получить заданную плотность
    while len(oriented_edges) < min_edges + additional_edges_count:
        u = random.randint(0, N - 1)
        v = random.randint(0, N - 1)
        if u != v and (u, v) not in existing:
            oriented_edges.append((u, v))
            existing.add((u, v))

    return oriented_edges

if __name__ == "__main__":
    # Получить параметр N из командной строки
    if len(sys.argv) < 2:
        print("Использование: python script.py N")
        sys.exit(1)
    
    N = int(sys.argv[1])
    graph_edges = generate_weakly_connected_digraph(N, 0.9)
    print("digraph G {")
    for u, v in graph_edges:
        print("    ", u, "->", v, " [label=", random.randint(1, 10), "];", sep='')
    print("}")