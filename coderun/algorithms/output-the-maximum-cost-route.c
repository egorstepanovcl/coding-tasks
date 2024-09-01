// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 3. Вывести маршрут максимальной стоимости

// Задача:
// В левом верхнем углу прямоугольной таблицы размером N×M находится черепашка. В каждой клетке таблицы записано некоторое число. Черепашка может перемещаться вправо или вниз, при этом маршрут черепашки заканчивается в правом нижнем углу таблицы.
// Подсчитаем сумму чисел, записанных в клетках, через которую проползла черепашка (включая начальную и конечную клетку). Найдите наибольшее возможное значение этой суммы и маршрут, на котором достигается эта сумма.

// Формат ввода:
// В первой строке входных данных записаны два натуральных числа N и M, не превосходящих 100 — размеры таблицы. Далее идет N строк, каждая из которых содержит M чисел, разделенных пробелами — описание таблицы. Все числа в клетках таблицы целые и могут принимать значения от 0 до 100.

// Формат вывода:
// Первая строка выходных данных содержит максимальную возможную сумму, вторая — маршрут, на котором достигается эта сумма. Маршрут выводится в виде последовательности, которая должна содержать N-1 букву D, означающую передвижение вниз и M-1 букву R, означающую передвижение направо. Если таких последовательностей несколько, необходимо вывести ровно одну (любую) из них.

// Ограничения:
// Ограничение времени: 1 с
// Ограничение памяти: 256 МБ

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define max(a, b) ((a) > (b) ? (a) : (b))

int grid[MAXN][MAXN];
int dp[MAXN][MAXN];
char path[MAXN * 2];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // Чтение входных данных
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Инициализация динамического программирования
    dp[0][0] = grid[0][0];

    // Заполнение первой строки
    for (int j = 1; j < M; ++j) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }

    // Заполнение первого столбца
    for (int i = 1; i < N; ++i) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }

    // Заполнение остальной части таблицы
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < M; ++j) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }

    // Реконструкция пути
    int x = N - 1, y = M - 1;
    int path_len = 0;

    while (x > 0 || y > 0) {
        if (x == 0) {
            path[path_len++] = 'R';
            --y;
        } else if (y == 0) {
            path[path_len++] = 'D';
            --x;
        } else if (dp[x-1][y] > dp[x][y-1]) {
            path[path_len++] = 'D';
            --x;
        } else {
            path[path_len++] = 'R';
            --y;
        }
    }

    // Переворачиваем путь
    for (int i = 0; i < path_len / 2; ++i) {
        char temp = path[i];
        path[i] = path[path_len - 1 - i];
        path[path_len - 1 - i] = temp;
    }
    path[path_len] = '\0';

    // Вывод результата
    printf("%d\n", dp[N-1][M-1]);
    printf("%s\n", path);

    return 0;
}