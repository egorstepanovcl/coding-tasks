#!/bin/bash

# Решил: Егор Степанов <https://github.com/egorstepanovcl>

# Название: 193. Действительные телефонные номера (193. Valid Phone Numbers)

# Задача:
# Имея текстовый файл file.txt, содержащий список телефонных номеров (по одному в строке), напишите однострочный bash-скрипт, который выведет все допустимые телефонные номера.
# Вы можете предположить, что действительный телефонный номер должен иметь один из следующих двух форматов: (xxx) xxx-xxxx или xxx-xx-xxxx. (x означает цифру).
# Также можно предположить, что каждая строка в текстовом файле не должна содержать ведущих или завершающих белых пробелов.

# Пример:
# Предположим, что файл file.txt имеет следующее содержание:
# 987-123-4567
# 123 456 7890
# (123) 456-7890
# Ваш скрипт должен вывести следующие правильные телефонные номера:
# 987-123-4567
# (123) 456-7890

grep -E '^(\([0-9]{3}\) [0-9]{3}-[0-9]{4}|[0-9]{3}-[0-9]{3}-[0-9]{4})$' file.txt