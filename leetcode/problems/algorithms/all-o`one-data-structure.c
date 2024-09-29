// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 432. Структура данных All O`one (432. All O`one Data Structure)

// Задача:
// Разработайте структуру данных для хранения количества строк с возможностью возврата строк с минимальным и максимальным количеством.
// Реализуйте класс AllOne:
// AllOne() Инициализирует объект структуры данных.
// inc(String key) Увеличивает счетчик строки key на 1. Если ключ не существует в структуре данных, вставьте его со счетом 1.
// dec(String key) Уменьшает счетчик строки key на 1. Если после декремента счетчик key равен 0, удалите его из структуры данных. Гарантируется, что key существует в структуре данных до декремента.
// getMaxKey() Возвращает один из ключей с максимальным значением count. Если ни один элемент не существует, возвращается пустая строка "".
// getMinKey() Возвращает один из ключей с минимальным количеством. Если элемент не существует, верните пустую строку "".
// Обратите внимание, что каждая функция должна выполняться со средней временной сложностью O(1).

// Пример 1:
// Вход
// ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
// [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
// Выход
// [null, null, null, "hello", "hello", null, "hello", "leet"]
// Пояснение
// AllOne allOne = new AllOne();
// allOne.inc(«hello»);
// allOne.inc(«hello»);
// allOne.getMaxKey(); // возвращаем "hello"
// allOne.getMinKey(); // возвращается "hello"
// allOne.inc(«leet»);
// allOne.getMaxKey(); // возвращаем "hello"
// allOne.getMinKey(); // возвращается "leet"

// Ограничения:
// 1 <= key.length <= 10
// Ключ состоит из строчных английских букв.
// Гарантируется, что для каждого вызова dec, key существует в структуре данных.
// Будет сделано не более 5 * 10⁴ вызовов inc, dec, getMaxKey и getMinKey.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int count;
    struct Node *prev, *next;
    char **keys;
    int keyCount;
} Node;

typedef struct {
    Node *head, *tail;
    Node *map[10000]; // Предполагаем фиксированный размер для простоты
} AllOne;

// Функция для создания нового узла
Node* createNode(int count) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->count = count;
    newNode->prev = newNode->next = NULL;
    newNode->keys = (char**)malloc(100 * sizeof(char*)); // Предполагаем максимум 100 ключей
    newNode->keyCount = 0;
    return newNode;
}

// Инициализация структуры данных
AllOne* allOneCreate() {
    AllOne* obj = (AllOne*)malloc(sizeof(AllOne));
    obj->head = createNode(INT_MIN);
    obj->tail = createNode(INT_MAX);
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;
    memset(obj->map, 0, sizeof(obj->map));
    return obj;
}

// Добавить новый узел с заданным счётом после указанного узла
Node* addNodeAfter(Node* node, int count) {
    Node* newNode = createNode(count);
    newNode->prev = node;
    newNode->next = node->next;
    node->next->prev = newNode;
    node->next = newNode;
    return newNode;
}

// Удалить узел, если в нём нет ключей
void removeNode(AllOne* obj, Node* node) {
    if (node->keyCount == 0) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node->keys);
        free(node);
    }
}

// Увеличить счётчик для ключа
void allOneInc(AllOne* obj, char* key) {
    int found = 0;
    for (int i = 0; i < 10000; i++) {
        if (obj->map[i] && strcmp(obj->map[i]->keys[0], key) == 0) {
            found = 1;
            Node* currentNode = obj->map[i];
            currentNode->keyCount--;
            int newCount = currentNode->count + 1;
            Node* nextNode = currentNode->next;
            if (nextNode->count != newCount) {
                nextNode = addNodeAfter(currentNode, newCount);
            }
            nextNode->keys[nextNode->keyCount++] = key;
            obj->map[i] = nextNode;
            removeNode(obj, currentNode);
            break;
        }
    }
    if (!found) {
        Node* firstNode = obj->head->next;
        if (firstNode->count != 1) {
            firstNode = addNodeAfter(obj->head, 1);
        }
        firstNode->keys[firstNode->keyCount++] = key;
        obj->map[0] = firstNode; // Предполагаем, что ключ уникален для простоты
    }
}

// Уменьшить счётчик для ключа
void allOneDec(AllOne* obj, char* key) {
    for (int i = 0; i < 10000; i++) {
        if (obj->map[i] && strcmp(obj->map[i]->keys[0], key) == 0) {
            Node* currentNode = obj->map[i];
            currentNode->keyCount--;
            if (currentNode->count == 1) {
                // Удалить ключ, если счётчик становится равным 0
                obj->map[i] = NULL;
                free(currentNode->keys);
                free(currentNode);
            } else {
                int newCount = currentNode->count - 1;
                Node* prevNode = currentNode->prev;
                if (prevNode->count != newCount) {
                    prevNode = addNodeAfter(currentNode->prev, newCount);
                }
                prevNode->keys[prevNode->keyCount++] = key;
                obj->map[i] = prevNode;
            }
            removeNode(obj, currentNode);
            break;
        }
    }
}

// Получить ключ с максимальным счётом
char* allOneGetMaxKey(AllOne* obj) {
    if (obj->tail->prev == obj->head) return ""; // Нет ключей
    return obj->tail->prev->keys[0]; // Возвращаем любой ключ с максимальным счётом
}

// Получить ключ с минимальным счётом
char* allOneGetMinKey(AllOne* obj) {
    if (obj->head->next == obj->tail) return ""; // Нет ключей
    return obj->head->next->keys[0]; // Возвращаем любой ключ с минимальным счётом
}

// Освобождаем структуру AllOne
void allOneFree(AllOne* obj) {
    // Освободить память здесь...
}

int main() {
    AllOne* obj = allOneCreate();
    allOneInc(obj, "key1");
    allOneInc(obj, "key2");
    allOneInc(obj, "key1");
    printf("Max Key: %s\n", allOneGetMaxKey(obj));
    printf("Min Key: %s\n", allOneGetMinKey(obj));
    allOneDec(obj, "key1");
    printf("Max Key: %s\n", allOneGetMaxKey(obj));
    printf("Min Key: %s\n", allOneGetMinKey(obj));
    allOneFree(obj);
    return 0;
}