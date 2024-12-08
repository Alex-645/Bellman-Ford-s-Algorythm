#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Структура для описания рёбер графа
struct Edge {
    int u, v, w; // u - начало, v - конец, w - вес
};

const int INF = INT_MAX; // Представление бесконечности

vector<Edge> edges;  // Список рёбер
vector<int> distances;  // Массив расстояний
int V, E, start;  // Количество вершин, рёбер и стартовая вершина

// Функция алгоритма Беллмана-Форда
void bellman_ford(int start) {
    distances[start] = 0;  // Расстояние до стартовой вершины равно 0

    // Релаксация всех рёбер (V - 1) раз
    for (int i = 0; i < V - 1; ++i) {
        for (auto edge : edges) {
            if (distances[edge.u] != INF && distances[edge.u] + edge.w < distances[edge.v]) {
                distances[edge.v] = distances[edge.u] + edge.w;
            }
        }
    }

    // Проверка на наличие отрицательных циклов
    for (auto edge : edges) {
        if (distances[edge.u] != INF && distances[edge.u] + edge.w < distances[edge.v]) {
            cout << "Граф содержит отрицательный цикл!" << endl;
            return;
        }
    }

    // Вывод кратчайших расстояний
    for (int i = 0; i < V; ++i) {
        cout << "Расстояние от вершины " << start + 1 << " до вершины " << i + 1 << " = ";
        if (distances[i] == INF)
            cout << "Нет пути" << endl;
        else
            cout << distances[i] << endl;
    }
}

// Функция ввода данных из консоли
bool input_data() {
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    if (V <= 0 || E < 0) {
        cerr << "Ошибка: количество вершин и рёбер должно быть положительным!" << endl;
        return false;
    }

    edges.resize(E);
    distances.assign(V, INF);

    cout << "Введите рёбра в формате (начало конец вес):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 1 || u > V || v < 1 || v > V) {
            cerr << "Ошибка: номера вершин должны быть в диапазоне от 1 до " << V << "!" << endl;
            return false;
        }

        edges[i] = { u - 1, v - 1, w }; // Сохраняем рёбра (нумерация с 0)
    }

    cout << "Введите стартовую вершину: ";
    cin >> start;

    if (start < 1 || start > V) {
        cerr << "Ошибка: стартовая вершина должна быть в диапазоне от 1 до " << V << "!" << endl;
        return false;
    }

    start -= 1; // Приводим к нумерации с 0
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 65001 > nul");
    if (!input_data()) {
        return 1; // Завершаем программу в случае ошибки ввода
    }

    cout << "Список кратчайших путей:" << endl;
    bellman_ford(start);

    return 0;
}