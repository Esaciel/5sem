import matplotlib.pyplot as plt
import numpy as np

def gradient_block(ax, x, y, kind):
    N = 20
    grad = np.zeros((N, N, 4))

    if "updated" in kind:
        rx, ry = np.meshgrid(np.linspace(0, 1, N), np.linspace(0, 1, N))
        grad[...,0] += rx * (1 - ry) # Red channel
        grad[...,3] += 0.5 * rx * (1 - ry) # Alpha

    if "depended" in kind:
        bx, by = np.meshgrid(np.linspace(0, 1, N), np.linspace(0, 1, N))
        grad[...,2] += (1 - bx) * by # Blue channel
        grad[...,3] += 0.5 * ((1 - bx) * by) # Alpha
    grad[...,3] = np.clip(grad[...,3], 0, 1)
    ax.imshow(grad, extent=(x, x+1, y, y+1), origin='lower')

blocks = 4
phases = 4
#labels = [["$W_{%d,%d}$" % (i+1,j+1) for j in range(blocks)] for i in range(blocks)]
labels = [["" for j in range(blocks)] for i in range(blocks)]

updated = [
    [(1,1)],
    [(0,1), (2,1), (3,1)],
    [(1,0), (1,2), (1,3)],
    [(0,0), (0,2), (0,3), (2,0), (2,2), (2,3), (3,0), (3,2), (3,3)]
]
depended = [
    [(1,1)],
    [(0,1), (1,1), (2,1), (3,1)],
    [(1,0), (1,1), (1,2), (1,3)],
    [(0,1), (2,1), (3,1), (1,0), (1,2), (1,3)]
]

fig, axes = plt.subplots(1, phases, figsize=(12,4), gridspec_kw={'wspace':0.25})
for p in range(phases):
    ax = axes[p]
    ax.set_xticks([])
    ax.set_yticks([])
    for i in range(blocks):
        for j in range(blocks):
            kind = []
            if (i, j) in updated[p]:
                kind.append("updated")
            if (i, j) in depended[p]:
                kind.append("depended")
            if kind:
                gradient_block(ax, j, blocks-1-i, kind)
            rect = plt.Rectangle((j, blocks-1-i), 1, 1, fill=False, edgecolor='black', linewidth=1.2)
            ax.add_patch(rect)
            ax.text(j+0.5, blocks-1-i+0.5, labels[i][j], ha='center', va='center', fontsize=13)
    ax.set_xlim(0,blocks)
    ax.set_ylim(0,blocks)
    ax.set_title(f'Фаза {p+1}', fontsize=13)

plt.rcParams['svg.fonttype'] = 'none'

plt.savefig("inf_dep_lbl.svg")
plt.show()