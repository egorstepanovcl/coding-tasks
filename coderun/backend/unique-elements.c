// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 155. Уникальные элементы

// Задача:
// Задан массив a размера n. Необходимо посчитать количество уникальных элементов в данном массиве. Элемент называется уникальным, если встречается в массиве ровно один раз.

// Формат ввода:
// В первой строке входных данных подается одно целое число n (1≤n≤10⁵).
// Во второй строке входных данных подается n целых чисел, разделенных пробелами − a₁, a₂, …, aₙ (1≤aᵢ≤10⁹).

// Формат вывода:
// В единственной строке выведите ответ на задачу.

// Ограничения:
// Ограничение времени: 2 с
// Ограничение памяти: 128 МБ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения элементов и их частоты
typedef struct {
    int key;
    int count;
} HashTableItem;

// Хэш-функция для маппинга значений в индексы
unsigned int hash(int key, int size) {
    return key % size;
}

// Функция для добавления элементов в хэш-таблицу
void add_to_hash_table(HashTableItem *table, int key, int size) {
    unsigned int index = hash(key, size);
    while (table[index].count != 0 && table[index].key != key) {
        index = (index + 1) % size;
    }
    if (table[index].count == 0) {
        table[index].key = key;
    }
    table[index].count++;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    // Создание хэш-таблицы с размером вдвое больше количества элементов
    int size = 2 * n;
    HashTableItem *hash_table = (HashTableItem *)calloc(size, sizeof(HashTableItem));
    
    // Добавление элементов в хэш-таблицу
    for (int i = 0; i < n; ++i) {
        add_to_hash_table(hash_table, arr[i], size);
    }

    // Подсчет уникальных элементов
    int unique_count = 0;
    for (int i = 0; i < size; ++i) {
        if (hash_table[i].count == 1) {
            unique_count++;
        }
    }

    printf("%d\n", unique_count);

    free(arr);
    free(hash_table);
    return 0;
}