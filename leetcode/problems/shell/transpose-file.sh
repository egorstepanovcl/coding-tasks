#!/bin/bash

# Решил: Егор Степанов <https://github.com/egorstepanovcl>

# Название: 194. Файл транспонирования (194. Transpose File)

# Задача:
# Задав текстовый файл file.txt, транспонируйте его содержимое.
# Можно считать, что в каждой строке одинаковое количество столбцов, а каждое поле разделено символом ' '.

# Пример:
# Если файл file.txt имеет следующее содержимое:
# name age
# alice 21
# ryan 30
# Выведите следующее:
# name alice ryan
# age 21 30

awk '{for (i=1; i<=NF; i++) {if (NR==1) {arr[i]=$i} else {arr[i]=arr[i] " " $i}}} END {for (i=1; i<=NF; i++) {print arr[i]}}' file.txt
