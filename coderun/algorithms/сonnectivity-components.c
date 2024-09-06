// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 8. Компоненты связности

// Задача:
// Дан неориентированный невзвешенный граф, состоящий из N вершин и M ребер. Необходимо посчитать количество его компонент связности и вывести их.
// Напомним:
// Компонента связности в неориентированном графе - это подмножество вершин, таких что все вершины достижимы друг из друга.

// Формат ввода:
// Во входном файле записано два числа N и M (0<N≤100000, 0≤M≤100000). В следующих M строках записаны по два числа i и j (1≤i,j≤N), которые означают, что вершины i и j соединены ребром.

// Формат вывода:
// В первой строчке выходного файла выведите количество компонент связности. Далее выведите сами компоненты связности в следующем формате: в первой строке количество вершин в компоненте, во второй - сами вершины в произвольном порядке.

// Ограничения:
// Ограничение времени: 2 с
// Ограничение памяти: 256 МБ

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

// Глобальные переменные
int visited[MAXN + 1];    // Массив посещённых вершин
int *adj[MAXN + 1];       // Списки смежности для графа
int adj_size[MAXN + 1];   // Размеры списков смежности для каждой вершины
int component[MAXN + 1];  // Для хранения вершин одной компоненты
int *components[MAXN + 1]; // Для хранения всех компонент
int comp_sizes[MAXN + 1];  // Для хранения размеров компонент
int total_components = 0;  // Общее количество компонент

// Функция для добавления ребра в граф
void add_edge(int u, int v) {
    adj[u] = (int*) realloc(adj[u], (adj_size[u] + 1) * sizeof(int));
    adj[v] = (int*) realloc(adj[v], (adj_size[v] + 1) * sizeof(int));
    adj[u][adj_size[u]++] = v;
    adj[v][adj_size[v]++] = u;
}

// Поиск в глубину (DFS)
void dfs(int v, int *size) {
    visited[v] = 1;
    component[(*size)++] = v;
    for (int i = 0; i < adj_size[v]; ++i) {
        int u = adj[v][i];
        if (!visited[u]) {
            dfs(u, size);
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // Чтение рёбер
    for (int i = 0; i < M; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    // Поиск компонент связности
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            int size = 0; // Размер текущей компоненты
            dfs(i, &size);

            // Сохранение компоненты
            components[total_components] = (int*) malloc(size * sizeof(int));
            for (int j = 0; j < size; ++j) {
                components[total_components][j] = component[j];
            }
            comp_sizes[total_components] = size;
            total_components++;
        }
    }

    // Вывод количества компонент
    printf("%d\n", total_components);

    // Вывод всех компонент
    for (int i = 0; i < total_components; ++i) {
        printf("%d\n", comp_sizes[i]);
        for (int j = 0; j < comp_sizes[i]; ++j) {
            printf("%d ", components[i][j]);
        }
        printf("\n");
    }

    // Освобождение памяти
    for (int i = 1; i <= N; ++i) {
        free(adj[i]);
    }
    for (int i = 0; i < total_components; ++i) {
        free(components[i]);
    }

    return 0;
}