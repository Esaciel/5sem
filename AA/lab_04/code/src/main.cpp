#include "definitions.hpp"
#include "io.hpp"
#include "measurements.hpp"
#include "solution.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <string>

#if defined(APP_TUI)
int main() {
  cout << "Задание: Дан граф. Найти все пары вершин на расстоянии (сумма меток "
          "дуг на пути) не большем, чем заданная "
          "на вход действительная величина."
       << endl;
  cout << "Введите имя файла с графом: " << endl;
  string filename;
  cin >> filename;
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Не удалось открыть файл" << endl;
    return 2;
  }
  graph g;
  parse_graphviz(g, file);
  auto adj = graph_to_adjecencyMatrix(g);
  cout << "Прочитанный граф:" << endl;
  print_graphviz(g);
  cout << "Матрица смежности: " << endl;
  print_adjMatrix(adj, g);
  cout << "Введите максимальное расстояние: " << endl;
  double max_gap;
  cin >> max_gap;
  cout << "Введите число потоков (0 - выполнится непараллельная реализация)"
       << endl;
  uint threads_num;
  cin >> threads_num;
  vector<Pair> res;
  if (threads_num == 0) {
    res = find_pairs_within_range__sequential(adj, max_gap);
  } else {
    res = find_pairs_within_range__parallel(adj, max_gap, threads_num);
  }
  cout << "Множество пар [A,B], у которых расстояние от A до B меньше "
       << max_gap << ":" << endl;
  print_pairs(res, g);
  return 0;
}
#elif defined(APP_CLI)
int main(int argc, char **argv) {
  if (argc < 4)
    return 1;
  ifstream file(argv[1]);
  if (!file.is_open())
    return 2;
  graph g;
  parse_graphviz(g, file);
  file.close();
  auto adj = graph_to_adjecencyMatrix(g);
  double max_gap = stod(argv[2]);
  size_t threads_num = stoi(argv[3]);
  vector<Pair> res;
  if (argc == 4) {
    if (threads_num == 0) {
      res = find_pairs_within_range__sequential(adj, max_gap);
    } else {
      res = find_pairs_within_range__parallel(adj, max_gap, threads_num);
    }
    print_pairs(res, g);
    return 0;
  } else // бэкдор для замеров, потому что лень думать
  {
    cout << measure(adj, max_gap, threads_num, stoi(argv[4])) << endl;
    return 0;
  }
}
#else
int main() {
  cout << "wrong build" << endl;
  exit(4);
}
#endif