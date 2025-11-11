import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load the data from CSV file
data = pd.read_csv('result_part1.csv', delimiter=';')

x = data['graphsize']

# Define colors that look distinct in color but also discernible in black and white
# Choose colors that convert well to different grayscale levels
colors = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink', 'black', 'tab:olive']

# Line styles for better distinction in black and white (varied solid/dashed/dotted)
linestyles = ['solid', 'dashed', 'dotted', 'dashdot', 'solid', 'dashed', 'dotted', 'dashdot', 'solid']

# Different markers for each line for point distinction
markers = ['o', 's', '^', 'D', 'v', 'P', '*', 'X', 'h']

# Prepare legend labels
labels = ['не параллельная реализация'] + ['однопоточная параллельная реализация'] + [f'параллельная реализация на {i} потоках' for i in [2, 4, 8, 16, 32, 64, 128]]

plt.figure(figsize=(10, 6))

for idx, col in enumerate(data.columns[1:]):
    plt.plot(x, data[col], label=labels[idx], color=colors[idx], linestyle=linestyles[idx], marker=markers[idx])

plt.xlabel('размер графа, число вершин')
plt.ylabel('Время выполнения, секунды')
plt.title('Сравнение времени выполнения параллельной и непараллельной реализаций')
plt.legend()
plt.grid(True, linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.savefig('result_part1_plot.pdf')
plt.close()
