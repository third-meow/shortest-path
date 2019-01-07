
def simple():
    node_n = 100000
    edges = []
    for i in range(1, node_n + 1):
        edges.append([i-1, i])
        edges.append([i, 0])
        edges.append([i, i-1])

    return edges, 0, node_n, node_n

def star():
    node_n = 100000
    edges = []
    for i in range(1, node_n + 1):
        edges.append([0, i])

    return edges, 0, node_n, node_n


edges, start, target, node_n = simple()

with open('data.txt', 'w') as f:
    f.write(f'{node_n}\n')
    f.write(f'{start} {target}\n')
    for edge in edges:
        f.write(f'{edge[0]} {edge[1]}\n')


