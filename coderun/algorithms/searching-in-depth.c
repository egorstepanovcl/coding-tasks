// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 7. Поиск в глубину

// Задача:
// Дан неориентированный граф, возможно, с петлями и кратными ребрами. Необходимо построить компоненту связности, содержащую вершину с номером 1.
// Напомним:
// Петля в графе - это ребро, которое соединяет вершину с самой собой.
// Кратные рёбра в графе - это ребра, которые соединяют одну и ту же пару вершин.
// Компонента связности в неориентированном графе - это подмножество вершин, таких что все вершины достижимы друг из друга.

// Формат ввода:
// В первой строке записаны два целых числа N (1≤N≤10³) и M (0≤M≤5∗10⁵) — количество вершин и ребер в графе. В последующих M строках перечислены ребра — пары чисел, определяющие номера вершин, которые соединяют ребра. Далее может идти произвольное количество пустых строк.

// Формат вывода:
// В первую строку выходного файла выведите число K — количество вершин в компоненте связности. Во вторую строку выведите K целых чисел — вершины компоненты связности, перечисленные в порядке возрастания номеров.

// Ограничения:
// Ограничение времени: 2 с
// Ограничение памяти: 256 МБ

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} List;

List graph[MAX_NODES];
bool visited[MAX_NODES];

// Функция для добавления ребра в граф
void addEdge(int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = v;
    node->next = graph[u].head;
    graph[u].head = node;
}

// Функция для поиска в глубину (DFS)
void dfs(int v, int* component, int* count) {
    visited[v] = true;
    component[*count] = v + 1; // Сохраняем вершину в компоненте
    (*count)++;

    Node* node = graph[v].head;
    while (node != NULL) {
        if (!visited[node->vertex]) {
            dfs(node->vertex, component, count); // Рекурсивный вызов DFS
        }
        node = node->next;
    }
}

// Функция сравнения для сортировки целых чисел
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b); // Исправлено: добавлена закрывающая скобка
}

int main() {
    int N, M;
    
    // Чтение количества вершин и рёбер
    scanf("%d %d", &N, &M);

    // Инициализация списка смежности
    for (int i = 0; i < N; ++i) {
        graph[i].head = NULL;
    }

    // Чтение рёбер и построение графа
    for (int i = 0; i < M; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u - 1, v - 1); // Добавление ребра
        if (u != v) {
            addEdge(v - 1, u - 1); // Граф неориентированный
        }
    }

    // Инициализация массива посещённых вершин
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }

    int component[MAX_NODES];
    int count = 0;

    // Поиск в глубину из вершины 1 (0 в нулевой индексации)
    dfs(0, component, &count);

    // Сортировка компоненты связности
    qsort(component, count, sizeof(int), compare);

    // Вывод результата
    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%d ", component[i]);
    }
    printf("\n");

    // Освобождение памяти
    for (int i = 0; i < N; ++i) {
        Node* node = graph[i].head;
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }

    return 0;
}