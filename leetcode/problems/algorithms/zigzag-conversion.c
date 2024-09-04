// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 6. Преобразование зигзага (6. Zigzag Conversion)

// Задача:
// Строка "PAYPALISHIRING" написана зигзагообразным узором на заданном количестве строк следующим образом: (для лучшей читаемости вы можете отобразить этот узор фиксированным шрифтом)
// P   A   H   N
// A P L S I I G
// Y   I   R
// А затем прочитайте строку за строкой: "PAHNAPLSIIGYIR"
// Напишите код, который будет принимать строку и выполнять преобразование, задавая количество строк:
// string convert(string s, int numRows);

// Пример 1:
// Вход: s = "PAYPALISHIRING", numRows = 3
// Выходные данные: "PAHNAPLSIIGYIR"

// Пример 2:
// Ввод: s = "PAYPALISHIRING", numRows = 4
// Выходные данные: "PINALSIGYAHRPI"
// Пояснение:
// P     I    N
// A   L S  I G
// Y A   H R
// P     I

// Пример 3:
// Вход: s = "A", numRows = 1
// Выходные данные: "A"

// Ограничения:
// 1 <= s.length <= 1000
// s состоит из английских букв (строчных и прописных), ',' и '.'.
// 1 <= numRows <= 1000

#include <stdlib.h>
#include <string.h>

// Функция для преобразования строки в зигзагообразный паттерн
char* convert(char* s, int numRows) {
    int len = strlen(s);
    if (numRows == 1 || numRows >= len) return s;

    // Выделяем память для результирующей строки
    char* result = (char*)malloc((len + 1) * sizeof(char));
    int index = 0; // Индекс для записи символов в результат

    int cycleLen = 2 * numRows - 2; // Длина одного цикла в зигзагообразном паттерне

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j + i < len; j += cycleLen) {
            result[index++] = s[j + i]; // Символы в первой колонке зигзага
            // Добавляем символы из диагонали (если они существуют)
            if (i != 0 && i != numRows - 1 && j + cycleLen - i < len) {
                result[index++] = s[j + cycleLen - i];
            }
        }
    }

    result[index] = '\0'; // Добавляем завершающий ноль в результирующую строку
    return result;
}