"""
Файл написан руками электронного разнорабочего под кодовым именем DeepSick,
потому что рисовать графики в matplotlib своими руками:
1) долго;
2) скучно;
3) объективно бессмысленно с точки зрения образования
   (и умственного развития в целом).
 ____
/~ .^\
\ <3 /
"""

import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

colorpair = ['black', 'lightblue']
colortriple = ['black', 'lightblue', 'red']

# Чтение данных из CSV файла
df = pd.read_csv('data.csv')  # замените 'data.csv' на имя вашего файла

# Разделение данных на четные и нечетные размеры
df_odd = df[df['size'] % 2 == 1].copy()
df_even = df[df['size'] % 2 == 0].copy()

# Сортировка данных по размеру для правильного соединения линиями
df_odd = df_odd.sort_values('size')
df_even = df_even.sort_values('size')

# Функция для преобразования в кубическую шкалу
def cubic_scale(y):
    """
    БОЛЕЕ НЕ ИСПОЛЬЗУЕТСЯ!!!
    сейчас - возвращает подаваемое значение без изменений
    """
    return y

# 1. std(odd) vs std(even) - отдельный график
plt.figure(figsize=(10, 6))
plt.plot(df_odd['size'], cubic_scale(df_odd['std']), 'o-', color=colorpair[0], linewidth=2, markersize=6, label='Нечетные размеры')
plt.plot(df_even['size'], cubic_scale(df_even['std']), 'x-', color=colorpair[1], linewidth=2, markersize=6, label='Четные размеры')
plt.title('Стандартный алгоритм: сравнение четных и нечетных размеров')
plt.xlabel('Размер матрицы')
plt.ylabel('Время выполнения, мc')
plt.gca().yaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('std_odd_vs_even.pdf', format='pdf')
#plt.show()

# 2. Win(odd) vs Win(even) - отдельный график
plt.figure(figsize=(10, 6))
plt.plot(df_odd['size'], cubic_scale(df_odd['Winograd']), 'o-', color=colorpair[0], linewidth=2, markersize=6, label='Нечетные размеры')
plt.plot(df_even['size'], cubic_scale(df_even['Winograd']), 'x-', color=colorpair[1], linewidth=2, markersize=6, label='Четные размеры')
plt.title('Алгоритм Винограда: сравнение четных и нечетных размеров')
plt.xlabel('Размер матрицы')
plt.ylabel('Время выполнения, мс')
plt.gca().yaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('winograd_odd_vs_even.pdf', format='pdf')
#plt.show()

# 3. optWin(odd) vs optWin(even) - отдельный график
plt.figure(figsize=(10, 6))
plt.plot(df_odd['size'], cubic_scale(df_odd['optWinograd']), 'o-', color=colorpair[0], linewidth=2, markersize=6, label='Нечетные размеры')
plt.plot(df_even['size'], cubic_scale(df_even['optWinograd']), 'x-', color=colorpair[1], linewidth=2, markersize=6, label='Четные размеры')
plt.title('Оптимизированный Виноград: сравнение четных и нечетных размеров')
plt.xlabel('Размер матрицы')
plt.ylabel('Время выполнения, мc')
plt.gca().yaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('optwinograd_odd_vs_even.pdf', format='pdf')
#plt.show()

# 4. Все алгоритмы на нечетных размерах - отдельный график
plt.figure(figsize=(10, 6))
plt.plot(df_odd['size'], cubic_scale(df_odd['std']), 'o-', color=colortriple[0], linewidth=2, markersize=6, label='Стандартный алгоритм')
plt.plot(df_odd['size'], cubic_scale(df_odd['Winograd']), '_-', color=colortriple[2], linewidth=2, markersize=6, label='Алгоритм Винограда')
plt.plot(df_odd['size'], cubic_scale(df_odd['optWinograd']), 'x-', color=colortriple[1], linewidth=2, markersize=6, label='Оптимизированный алгоритм Винограда')
plt.title('Сравнение всех алгоритмов (нечетные размеры)')
plt.xlabel('Размер матрицы')
plt.ylabel('Время выполнения, мc')
plt.gca().yaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('all_algorithms_odd.pdf', format='pdf')
#plt.show()

# 5. Все алгоритмы на четных размерах - отдельный график
plt.figure(figsize=(10, 6))
plt.plot(df_even['size'], cubic_scale(df_even['std']), 'o-', color=colortriple[0], linewidth=2, markersize=6, label='Стандартный алгоритм')
plt.plot(df_even['size'], cubic_scale(df_even['Winograd']), '_-', color=colortriple[2], linewidth=2, markersize=6, label='Алгоритм Винограда')
plt.plot(df_even['size'], cubic_scale(df_even['optWinograd']), 'x-', color=colortriple[1], linewidth=2, markersize=6, label='Оптимизированный алгоритм Винограда')
plt.title('Сравнение всех алгоритмов (четные размеры)')
plt.xlabel('Размер матрицы')
plt.ylabel('Время выполнения, мc')
plt.gca().yaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('all_algorithms_even.pdf', format='pdf')
#plt.show()
