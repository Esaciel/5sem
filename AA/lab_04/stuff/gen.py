import random
import sys

def generate_weakly_connected_digraph(N, extra_edges_ratio=0.3):
    """
    Генерирует слабо-связанный ориентированный граф с N вершинами.
    
    extra_edges_ratio - доля дополнительных ребер относительно минимального числа ребер (N-1)
    для усложнения графа.
    """
    if N < 1:
        return []
    
    edges = []
    # 1. Генерация остовного дерева (сначала создаём неориентированный связный граф)
    vertices = list(range(N))
    random.shuffle(vertices)
    connected = {vertices[0]}
    remaining = set(vertices[1:])
    
    while remaining:
        u = random.choice(tuple(connected))
        v = random.choice(tuple(remaining))
        # Добавляем ребро u-v как неориентированное (без направления)
        edges.append((u,v))  # напр. для остова ориентируем позже
        connected.add(v)
        remaining.remove(v)
    
    # 2. Ориентируем рёбра остова случайно
    oriented_edges = []
    for (u,v) in edges:
        if random.choice([True, False]):
            oriented_edges.append((u,v))
        else:
            oriented_edges.append((v,u))
    
    # 3. Добавляем дополнительные случайные ребра с ориентацией
    max_possible_edges = N*(N-1)
    current_edges = len(oriented_edges)
    extra_edges = int(extra_edges_ratio * (N-1))
    total_edges = current_edges + extra_edges
    existing = set(oriented_edges)
    
    while len(oriented_edges) < total_edges:
        u = random.randint(0, N-1)
        v = random.randint(0, N-1)
        if u != v and (u,v) not in existing:
            oriented_edges.append((u,v))
            existing.add((u,v))
    
    return oriented_edges

if __name__ == "__main__":
    # Получить параметр N из командной строки
    if len(sys.argv) < 2:
        print("Использование: python script.py N")
        sys.exit(1)
    
    N = int(sys.argv[1])
    graph_edges = generate_weakly_connected_digraph(N)
    print("digraph G {")
    for u, v in graph_edges:
        print("    ", u, "->", v, " [label=", random.randint(1, 10), "];", sep='')
    print("}")