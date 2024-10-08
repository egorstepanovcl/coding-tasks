// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 6. НОП с восстановлением ответа

// Задача:
// Даны две последовательности, требуется найти и вывести их наибольшую общую подпоследовательность.
// Напомним:
// Последовательность x называется подпоследовательностью последовательности y, если x получается из y удалением нескольких (возможно, нуля или всех) элементов.
// Наибольшая общая подпоследовательность - последовательность наибольшей длины, которая является подпоследовательностью обеих последовательностей.

// Формат ввода:
// В первой строке входных данных содержится число N – длина первой последовательности (1≤N≤1000). Во второй строке заданы члены первой последовательности (через пробел) – целые числа, не превосходящие 10000 по модулю.
// В третьей строке записано число M – длина второй последовательности (1≤M≤1000). В четвертой строке задаются члены второй последовательности (через пробел) – целые числа, не превосходящие 10000 по модулю.

// Формат вывода:
// Требуется вывести наибольшую общую подпоследовательность данных последовательностей, через пробел. Если таких подпоследовательностей несколько, то можно вывести любую.

// Примечание:
// В примере 2 существует сразу три наибольшие общие подпоследовательности.
// 1) 1
// 2) 2
// 3) 3
// Любая из них будет правильным ответом.

// Ограничения:
// Ограничение времени: 1 с
// Ограничение памяти: 64 МБ

#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    
    // Чтение длины первой последовательности
    scanf("%d", &N);
    int* seq1 = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) {
        scanf("%d", &seq1[i]);
    }

    // Чтение длины второй последовательности
    scanf("%d", &M);
    int* seq2 = (int*)malloc(M * sizeof(int));
    for (int i = 0; i < M; ++i) {
        scanf("%d", &seq2[i]);
    }

    // Создание таблицы для хранения длин НОП
    int** dp = (int**)malloc((N + 1) * sizeof(int*));
    for (int i = 0; i <= N; ++i) {
        dp[i] = (int*)malloc((M + 1) * sizeof(int));
    }

    // Заполнение таблицы
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; // База: если одна из последовательностей пустая
            } else if (seq1[i - 1] == seq2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Если элементы равны, увеличиваем длину
            } else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]; // Иначе берем максимум
            }
        }
    }

    // Восстановление НОП из таблицы
    int length = dp[N][M];
    int* lcs = (int*)malloc(length * sizeof(int));
    int index = length - 1;
    int i = N, j = M;

    while (i > 0 && j > 0) {
        if (seq1[i - 1] == seq2[j - 1]) {
            lcs[index] = seq1[i - 1]; // Записываем элемент НОП
            index--;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Вывод НОП
    for (int i = 0; i < length; i++) {
        printf("%d ", lcs[i]);
    }
    printf("\n");

    // Освобождение памяти
    free(seq1);
    free(seq2);
    free(lcs);
    for (int i = 0; i <= N; ++i) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}