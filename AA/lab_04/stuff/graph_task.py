import pandas as pd
import matplotlib.pyplot as plt

def plot_from_csv(file_path):
    # Читаем CSV в DataFrame
    df = pd.read_csv(file_path, sep=';')
    
    # Проверяем наличие нужных столбцов
    if not {'n', 'rec', 'nonrec'}.issubset(df.columns):
        raise ValueError("CSV должен содержать столбцы 'n', 'rec', 'nonrec'")
    
    # Строим график
    plt.figure(figsize=(8, 5))
    plt.plot(df['n'], df['rec'] * 1000, marker='o', label='рекурсивный алгоритм')
    plt.plot(df['n'], df['nonrec'] * 1000, marker='x', label='итеративный алгоритм')
    plt.xlabel('Граница вывода')
    plt.ylabel('Время выполнения, мс')
    plt.title('Выполнение рекурсивного и итеративного алгоритмов')
    plt.legend()
    plt.grid(True)
    plt.show()

# Пример вызова:
plot_from_csv('results.csv')